#!/usr/bin/env python
from configtool import ConfigFile, defaultConfigFile
import pbutil
import tempfile, os, math, warnings, random, sys, subprocess, time
import shutil
import storagedirs
import tunerwarnings 
import platform
import numpy
from copy import deepcopy
from storagedirs import timers
from scipy import stats
from collections import defaultdict
from tunerconfig import config, OperatorSelectionMethod
from tunerwarnings import ComparisonFailed, InconsistentOutput
import mutators
warnings.simplefilter('ignore', DeprecationWarning)
numpy.seterr(all="ignore")

def getMemoryLimitArgs():
  limit = []
  if platform.machine() == 'x86_64' and platform.system() == 'Linux':
    mi = filter(lambda x: x[0:9]=="MemTotal:", open("/proc/meminfo"))
    assert len(mi)==1
    v,u = mi[0][9:].strip().split(' ')
    v=int(v)
    assert u=="kB"
    limit=['--max-memory=%d'%int(v*1024*config.memory_limit_pct)]
  global getMemoryLimitArgs
  getMemoryLimitArgs = lambda: limit
  return limit

class NoMutators(Exception):
  '''Exception thrown when a mutation doesn`t exist'''
  pass

class InputGenerationException(Exception):
  def __init__(self, testNumber, cmd):
    self.testNumber = int(testNumber)
    self.cmd = cmd

  def __str__(self):
    return repr(self)
  
  def __repr__(self):
    return 'InputGenerationException(%d, "%s")' % (self.testNumber, str(self.cmd))

class CrashException(Exception):
  def __init__(self, testNumber, n, candidate, cmd):
    self.testNumber=testNumber
    self.n = n
    self.candidate=candidate
    self.cmd=cmd
    self.debugpause()
  def debugpause(self):
    if config.pause_on_crash:
      print '-'*60
      print 'ERROR: Candidate algorithm crashed!'
      print '-'*60
      print "%s crashed on test %d for input size %d" % (str(self.candidate),self.testNumber, self.n)
      print 'cmd:', ' '.join(self.cmd)
      print 'set config.pause_on_crash=False to disable this message'
      print '-'*60
      print
      import progress
      progress.pause('press any key to continue')

def debug_logcmd(cmd):
 #print ' '.join(cmd)
 #sys.stdout.flush()
 #open("lastcmd","w").write(' '.join(cmd))
  pass

class Results:
  '''stores a list of (timing|accuracy) test results and collects statistics'''
  def __init__(self, results=[]):
    self.realResults=[]         #listof(float)
    self.timeoutResults=[]      #listof(float)
    self.interpolatedResults=[] #listof(float)
    self.distribution = None


  def discard(self, n):
    if len(self.realResults)>n:
      self.realResults = self.realResults[-n:]
      self.timeoutResults = []
      self.reinterpolate()

  def __repr__(self):
    v=[]
    v.extend(map(lambda x: "%.6f"%x,  self.realResults))
    v.extend(map(lambda x: ">%.6f"%x, self.timeoutResults))
    return ', '.join(v)

  def __str__(self):
    if len(self)==0:
      return '???'
    return "%.6f(+-%.6f)" % self.interval(config.display_confidence)

  def strdelta(a, b):
    am, ad = a.interval(config.display_confidence)
    bm, bd = b.interval(config.display_confidence)
    return "%.2fx to %.2fx" % (
        max(0.0, am+ad)/max(1e-32, bm-bd),
        max(0.0, am-ad)/max(1e-32, bm+bd)
        )

  def interval(self, conf):
    md=self.meanDistribution()
    a=md.ppf((1.0-conf)/2.0)
    mean=md.ppf(0.5)
    delta = mean-a
    return mean, delta

  def reasonableLimit(self):
    dd=self.dataDistribution()
    return dd.ppf(config.limit_conf_pct)*config.limit_multiplier

  def __len__(self):
    return len(self.realResults)+len(self.timeoutResults)

  def add(self, p):
    self.realResults.append(p)
    self.reinterpolate();

  def addTimeout(self, p):
    assert p is not None
    self.timeoutResults.append(p)
    self.reinterpolate();

  def numTimeouts(self):
    return len(self.timeoutResults)

  def reinterpolate(self):
    '''recreate interpolatedResults from realResults and timeoutResults'''
    self.interpolatedResults = list(self.realResults)
    def mkdistrib():
      m=numpy.mean(self.interpolatedResults) 
      s=max(config.min_std_pct*m,numpy.std(self.interpolatedResults))
      if s==0.0:
        s = 1e-10
      return stats.norm(m,s)
    if len(self.interpolatedResults) == 0:
      '''all tests timed out, seed with double the average timeout'''
      self.interpolatedResults.append(sum(self.timeoutResults)/len(self.timeoutResults)*2.0)
    if len(self.interpolatedResults) == 1:
      '''only 1 test, use prior stddev'''
      s = abs(self.interpolatedResults[0]*config.prior_stddev_pct)
      if s==0.0:
        s = 1e-10
      self.distribution = stats.norm(self.interpolatedResults[0], s)
    else:
      '''estimate stddev with least squares'''
      self.distribution = mkdistrib()
    for p in sorted(self.timeoutResults):
      '''now lets estimate values for the points that timed out'''
      '''new points are assigned the median value above their timeout'''
      self.interpolatedResults.append(max(p, min(self.distribution.isf(self.distribution.sf(p)/2.0), p*4)))
      self.distribution = mkdistrib()
    if numpy.isnan(self.mean()) or numpy.isinf(self.mean()) \
        or numpy.isnan(self.variance()) or numpy.isinf(self.variance()):
      print "PROBLEM!!! EMAIL BELOW TO jansel"
      print self.mean(), self.variance()
      print self.realResults
      print self.timeoutResults
      print self.interpolatedResults
      assert False
 
  def dataDistribution(self):
    '''estimated probability distribution of a single timing run'''
    return self.distribution

  def meanDistribution(self):
    '''estimated probability distribution of the real mean value'''
    try:
      return stats.norm(self.mean(), math.sqrt(self.meanVariance()))
    except OverflowError:
      return self.distribution

  def mean(self):
    assert len(self)>0
    m,v=self.distribution.stats()
    return m
  
  def min(self):
    assert len(self)>0
    return min(self.interpolatedResults)

  def variance(self):
    assert len(self)>0
    m,v=self.distribution.stats()
    return v

  def meanVariance(self, offset=0):
    '''square of stderror'''
    assert len(self)>0
    return self.variance()/float(len(self)+offset)
  
  def stderr(self, offset=0):
    return math.sqrt(self.meanVariance())
  
  def invstderr(self, offset=0):
    return 1.0/math.sqrt(self.meanVariance())

  def estimatedBenifitNextTest(self, offset=1):
    return self.meanVariance()-self.meanVariance(offset)

  def ttest(self, that):
    '''estimate probability P(data | self and that have same mean)'''
    assert len(self)>0
    assert len(that)>0
    return stats.ttest_ind(self.interpolatedResults, that.interpolatedResults, 0)[1]

  def diffChance(self, that):
    '''estimate probability self and that have different means'''
    return 1.0 - self.ttest(that)

  def sameChance(self, that):
    '''estimate probability self and that have means within config.same_threshold_pct'''
    denom = min(self.mean(), that.mean())
    dd=stats.norm((self.mean()-that.mean())/denom, math.sqrt(self.meanVariance()+that.meanVariance())/denom)
    return dd.cdf(config.same_threshold_pct/2.0)-dd.cdf(-config.same_threshold_pct/2.0)

  def last(self):
    if self.realResults:
      return self.realResults[-1]

class ResultsDB:
  '''stores many Results for different input sizes'''
  def __init__(self, metric, vals=dict()):
    self.metric = metric
    self.nToResults = dict(vals)

  def __getitem__(self, n):
    try:
      return self.nToResults[n]
    except KeyError:
      self.nToResults[n]=Results()
      return self[n]
  
  def __setitem__(self, n, v):
    self.nToResults[n] = v

  def __repr__(self):
    return "ResultsDB(%s, {"%repr(self.metric)+\
           ', '.join(map(lambda x: "%d: %s"%(x[0], repr(x[1])), self.nToResults.iteritems()))+\
           "})"
           
  def __len__(self):
    return len(self.nToResults)
    
  def totalTests(self):
    return sum(map(len, self.nToResults.values()))

  def keys(self):
    return self.nToResults.keys()


class Candidate:
  nextCandidateId=0
  '''A candidate algorithm in the population'''
  def __init__(self, cfg, mlog=list()):
    self.config         = ConfigFile(cfg)
    self.startconfig    = ConfigFile(deepcopy(self.config))
    self.metrics        = [ResultsDB(x) for x in config.metrics]
    self.cid            = Candidate.nextCandidateId
    self.outputdir      = storagedirs.candidate(self.cid)
    self.mutationlog    = list(mlog)
    Candidate.nextCandidateId += 1

  def discardResults(self, n):
    for m in self.metrics:
      for k in m.keys():
        m[k].discard(n)

  def __str__(self):
    return "Candidate%d"%self.cid

  def clone(self):
    return Candidate(deepcopy(self.config), self.mutationlog)
  
  def reset_mutation_log(self):
    self.mutationlog = list()

  def log_mutation(self, m):
    self.mutationlog.append(m)

  def clearResultsAbove(self, val):
    for i in xrange(len(self.metrics)):
      for n in self.metrics[i].keys():
        if n>=val:
          self.metrics[i][n] = Results()

  def clearResults(self):
    for i in xrange(len(self.metrics)):
      for n in self.metrics[i].keys():
        self.metrics[i][n] = Results()

  def reasonableLimit(self, n):
    if self.numTests(n)>0:
      return self.metrics[config.timing_metric_idx][n].reasonableLimit()
    else:
      return None

  def resultsStr(self, n, baseline=None):
    s=['trials: %2d'%self.numTests(n)]
    t=str
    if config.print_raw:
      t=repr
    for i, m in enumerate(self.metrics):
      s.append("%s: %s" % (config.metrics[i], t(m[n])))
    return ', '.join(s)

  def resultsTable(self, n):
    l = [('candidate', str(self.cid)),
         ('trials', str(self.numTests(n)))]
    for i, m in enumerate(self.metrics):
      l.append((config.metrics[i], str(m[n])))
    l.append(('mutation_log', ''.join(map(lambda x: x.short, self.mutationlog)[-10:])))
    return l

  def numTests(self, n):
    return len(self.metrics[config.timing_metric_idx][n])

  def numTimeouts(self, n):
    return self.metrics[config.timing_metric_idx][n].numTimeouts()

  def isAllTimeout(self, n):
    return self.numTests(n) <= self.numTimeouts(n)
  
  def numTotalTests(self):
    return self.metrics[config.timing_metric_idx].totalTests()

  def performance(self, n):
    if len(self.metrics[config.timing_metric_idx][n]) == 0:
      return (2**31)
    return self.metrics[config.timing_metric_idx][n].mean()

  def accuracy(self, n):
    if len(self.metrics[config.accuracy_metric_idx][n]) == 0:
      return -(2**31)
    return self.metrics[config.accuracy_metric_idx][n].mean()

  def hasAccuracy(self, n, target):
    if len(self.metrics[config.accuracy_metric_idx][n]) == 0:
      return False
    if target is None:
      return True
    return self.metrics[config.accuracy_metric_idx][n].mean() >= target

  def cfgfile(self):
    cf=os.path.join(self.outputdir,'config')
    self.config.save(cf)
    return cf

  def rmfiles(self):
    for f in ('config', 'stats', 'stats_raw'):
      f=os.path.join(self.outputdir,f)
      if os.path.isfile(f):
        os.unlink(f)
    os.rmdir(self.outputdir)
  
  def timingResults(self, n=None):
    if n is None:
      n=max(self.metrics[config.timing_metric_idx].keys())
    return self.metrics[config.timing_metric_idx][n]

  def accuracyResults(self, n=None):
    if n is None:
      n=max(self.metrics[config.accuracy_metric_idx].keys())
    return self.metrics[config.accuracy_metric_idx][n]

  def writestats(self, n, filename=None):
    if filename is None:
      filename=os.path.join(self.outputdir,'stats')
    first=not os.path.isfile(filename)
    s=open(filename, 'a')
    if first:
      s.write("#input, ")
      for m in config.metrics:
        s.write("%s_mean, %s_stddev, %s_stderr, %s_ci, "%(m, m, m, m))
      s.write("\n")
    s.write("%6d, "%n)
    for m in self.metrics:
      try:
        avg,ci = m[n].interval(config.display_confidence)
        sd = math.sqrt(m[n].variance())
        se = math.sqrt(m[n].meanVariance())
      except OverflowError:
        if numpy.isinf(m[n].variance()):
          sd = numpy.inf
          se = numpy.inf
        else:
          raise
      except AssertionError:
        avg = -1
        ci = -1
        se = -1
        sd = -1

      s.write("%.8f, %.8f, %.8f, %.8f, "%(avg,sd,se,ci))
    s.write("\n")
    s.close()

class Input:
  def __init__(self, pfx):
    self.pfx=pfx
    self.outputHash=None
    self.firstCandidate=None

class MutatorLogFile:
  def __init__(self, mutators):
    self.mutators = sorted(mutators, key=str)
    self.mutatorPerf = storagedirs.openCsvStats("mutatorperf", ["gen", "time", "accuracy", "dtime", "daccuracy," "selected_mutator"])
    self.mutatorScores = storagedirs.openCsvStats("mutatorscores", ["gen"] + map(str, mutators))

  def logPerformance(self, gen, time, accuracy, dtime, daccuracy, selectedMutator):
    self.mutatorPerf.writerow([gen, time, accuracy, dtime, daccuracy, selectedMutator]);

  # scoreMap: a dictionary mutator -> (expl. term, exploit. term, score). All available mutators must be present.
  def logScores(self, gen, scoreMap):
    scores = map(lambda (m,score): score, sorted(scoreMap.items(), key=lambda (m,score): str(m)))
    self.mutatorScores.writerow([gen] + scores)
      

class CandidateTester:
  def __init__(self, app, n, args=[]):
    self.app = app
    self.bin = pbutil.benchmarkToBin(app)
    self.n = n + config.offset
    self.cmd = [
        self.bin,
        "--time",
        "--accuracy",
        "--threads=%d"%config.threads,
      ]
    self.cmd.extend(args)
    self.args=args
    self.inputs=[]
    self.testCount = 0
    self.timeoutCount = 0
    self.crashCount = 0
    self.wasTimeout = True 

  def nextTester(self):
    return CandidateTester(self.app, (self.n-config.offset)*2, self.args)

  def testN(self, candidate, trials, limit=None):
    for x in xrange(trials - candidate.numTests(self.n)):
      self.test(candidate, limit)

  def getInputArg(self, testNumber):
    if config.use_iogen:
      pfx=storagedirs.inputpfx(self.n, testNumber)
      if len(self.inputs) <= testNumber:
        assert len(self.inputs) == testNumber
        cmd = self.cmd + ['--iogen-create='+pfx, "--n=%d"%self.n]
        debug_logcmd(cmd)
        devnull = open("/dev/null", "w")
        try:
          if subprocess.call(cmd, stdout=devnull, stderr=devnull) != 0:
            raise InputGenerationException(testNumber, ' '.join(cmd))
          self.inputs.append(Input(pfx))
        finally:
          devnull.close()
      return ["--iogen-run="+pfx, "--iogen-n=%d"%self.n]
    else:
      return ["--n=%d"%self.n]

  def checkOutputHash(self, candidate, i, value):
    if self.inputs[i].outputHash is None:
      self.inputs[i].outputHash = value
      self.inputs[i].firstCandidate = candidate
    elif self.inputs[i].outputHash != value:
      warnings.warn(InconsistentOutput(self.inputs[i].firstCandidate, candidate, self.inputs[i].pfx))
      sys.stdout.flush()

  def test(self, candidate, limit=None):
    self.testCount += 1
    cfgfile = candidate.cfgfile()
    testNumber = candidate.numTests(self.n)
    if testNumber>=config.max_trials:
      warnings.warn(tunerwarnings.TooManyTrials(testNumber+1))
    cmd = list(self.cmd)
    cmd.append("--config="+cfgfile)
    #cmd.append("--noisolation")
    cmd.extend(timers.inputgen.wrap(lambda:self.getInputArg(testNumber)))
    if limit is not None:
      cmd.append("--max-sec=%f"%limit)
    cmd.extend(getMemoryLimitArgs())
    try:
      debug_logcmd(cmd)
      if config.check:
        results = timers.testing.wrap(lambda: pbutil.executeRun(cmd+['--hash'], config.metrics+['outputhash']))
        self.checkOutputHash(candidate, testNumber, results[-1]['value'])
        del results[-1]
      else:
        results = timers.testing.wrap(lambda: pbutil.executeRun(cmd, config.metrics))
      for i,result in enumerate(results):
        if result is not None:
          v=result['average']
          if numpy.isnan(v) or numpy.isinf(v):
            warnings.warn(tunerwarnings.NanAccuracy())
            raise pbutil.TimingRunFailed(None)
          candidate.metrics[i][self.n].add(v)
      return True
    except pbutil.TimingRunTimeout:
      assert limit is not None
      warnings.warn(tunerwarnings.ProgramTimeout(candidate, self.n, limit))
      candidate.metrics[config.timing_metric_idx][self.n].addTimeout(limit)
      self.timeoutCount += 1
      return False
    except pbutil.TimingRunFailed, e:
      self.crashCount += 1
      raise CrashException(testNumber, self.n, candidate, cmd)

  def race(self, candidatea, candidateb, limit=None, accuracy_target=None):
    self.testCount += 1
    cfgfilea = candidatea.cfgfile()
    if candidateb is None:
      cfgfileb = 'None'
    else:
      cfgfileb = candidateb.cfgfile()
    cmd = list(self.cmd)
    cmd.extend(timers.inputgen.wrap(lambda:self.getInputArg(0)))
    if limit is not None:
      cmd.append("--max-sec=%f"%limit)
    cmd.extend(getMemoryLimitArgs())
    cmd.extend(["--race-multiplier=%f" % config.race_multiplier,
                "--race-multiplier-lowacc=%f" % config.race_multiplier_lowacc,
                "--race-split-ratio=%f" % config.race_split_ratio])
    if accuracy_target:
      cmd.append("--race-accuracy=%f"%accuracy_target)
    try:
      debug_logcmd(cmd)
      resulta,resultb = timers.testing.wrap(lambda: pbutil.executeRaceRun(cmd, cfgfilea, cfgfileb))
      best = min(min(resulta['timing'], resultb['timing']), 2**31)
      if limit is not None and best>limit*2:
        best=limit
      for candidate, result in [(candidatea,resulta), (candidateb,resultb)]:
        if result['timing'] < 2**31:
          candidate.wasTimeout = False
          for i,metric in enumerate(config.metrics):
            candidate.metrics[i][self.n].add(result[metric])
        elif candidate is not None:
          candidate.metrics[config.timing_metric_idx][self.n].addTimeout(best)
          candidate.wasTimeout = True
      return True
    except pbutil.TimingRunTimeout:
      assert limit is not None
      warnings.warn(tunerwarnings.ProgramTimeout(candidate, self.n, limit))
      candidate.metrics[config.timing_metric_idx][self.n].addTimeout(limit)
      self.timeoutCount += 1
      return False
    except pbutil.TimingRunFailed, e:
      self.crashCount += 1
      raise CrashException(0, self.n, candidatea, cmd)
  
  def comparer(self, metricIdx, confidence, maxTests, limit=None):
    '''return a cmp like function that dynamically runs more tests to improve confidence'''
    def compare(a, b):
      assert a.numTests(self.n)>0
      assert b.numTests(self.n)>0
      if metricIdx != config.timing_metric_idx:
        if len(a.metrics[metricIdx][self.n])==0:
          warnings.warn(tunerwarnings.ComparisonSkipped(self.n, a, b))
          return 0
        if len(b.metrics[metricIdx][self.n])==0:
          warnings.warn(tunerwarnings.ComparisonSkipped(self.n, a, b))
          return 0

      for x in xrange(2*maxTests+1):
        ra=a.metrics[metricIdx][self.n]
        rb=b.metrics[metricIdx][self.n]
        if ra.diffChance(rb) >= confidence:
          # we can eliminate the null hypothesis, just compare
          return config.metric_orders[metricIdx]*cmp(ra.mean(), rb.mean())
        if ra.sameChance(rb) >= confidence:
          return 0
        if ra.estimatedBenifitNextTest() >= rb.estimatedBenifitNextTest() and a.numTests(self.n)<maxTests:
          self.test(a, limit=limit)
        elif b.numTests(self.n)<maxTests:
          self.test(b, limit=limit)
        elif a.numTests(self.n)<maxTests:
          self.test(a, limit=limit)
        else:
          break
      warnings.warn(ComparisonFailed(self.n, a, b))
      return 0
    return compare


  def testUntilConfident(self, a, b, limit=None):
    '''
    just a special case of the dynamic testing comparer
    '''
    cmpobj = self.comparer(config.timing_metric_idx,
                           config.confidence_pct,
                           config.max_trials,
                           limit)
    return cmpobj(a,b)

  def cleanup(self):
    if config.cleanup_inputs:
      storagedirs.clearInputs();
      self.inputs=[]

if __name__ == "__main__":
  print "TESTING CANDIDATETESTER"
  pbutil.chdirToPetabricksRoot();
  pbutil.compilePetabricks();
  benchmark=pbutil.normalizeBenchmarkName('multiply')
  pbutil.compileBenchmarks([benchmark])
  tester = CandidateTester(benchmark, 768)
  try:
    candidate = Candidate(defaultConfigFile(pbutil.benchmarkToBin(tester.app)))
    candidate2 = Candidate(defaultConfigFile(pbutil.benchmarkToBin(tester.app)))
    candidate2.config['MatrixMultiplyTransposed_0_lvl1_rule']=1
    tester.test(candidate)
    tester.test(candidate)
    tester.test(candidate)
    tester.test(candidate2)
    tester.test(candidate2)
    tester.test(candidate2)
    print candidate.metrics[0]
    print candidate2.metrics[0]
    print str(candidate.metrics[0][768])
    print str(candidate2.metrics[0][768])
    c=tester.comparer(0, .95, 25)
    print c(candidate, candidate2)
    print candidate.metrics[0][768].sameChance(candidate2.metrics[0][768])
    print candidate.metrics[0][768].diffChance(candidate2.metrics[0][768])
    print candidate.metrics[0]
    print candidate2.metrics[0]
  finally:
    tester.cleanup()





