/***************************************************************************
 *  Copyright (C) 2008-2009 Massachusetts Institute of Technology          *
 *                                                                         *
 *  This source code is part of the PetaBricks project and currently only  *
 *  available internally within MIT.  This code may not be distributed     *
 *  outside of MIT. At some point in the future we plan to release this    *
 *  code (most likely GPL) to the public.  For more information, contact:  *
 *  Jason Ansel <jansel@csail.mit.edu>                                     *
 *                                                                         *
 *  A full list of authors may be found in the file AUTHORS.               *
 ***************************************************************************/
#include "maximawrapper.h"

#include "common/jassert.h"
#include "common/jsocket.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

static int forkopen(void (*fn)()){
  int fds[2];
  JASSERT(socketpair(AF_UNIX, SOCK_STREAM, 0, fds)==0);
  pid_t pid = fork();
  JASSERT(pid>=0);
  if(pid>0){
    //parent
    close(fds[1]);
    return fds[0];
  }else{
    //child
    JASSERT(dup2(fds[1], 0)==0);
    JASSERT(dup2(fds[1], 1)==1);
    close(fds[0]);
    close(fds[1]);
    (*fn)();
    JASSERT(false);
    return -1;
  }
}

static void launchMaxima(){
  const char* args[]= {MAXIMA_PATH,"-q","--disable-readline", NULL};
  execvp(args[0],(char**)args);
  JASSERT(false)(JASSERT_ERRNO).Text("exec(maxima) failed");
}
#ifdef MAXIMA_LOG
static void launchMaximaWithLogging(){
  class LogForwarder : public jalib::JMultiSocketProgram {
  public:
    void onConnect ( const jalib::JSocket& /*sock*/, const struct sockaddr* /*remoteAddr*/, socklen_t /*remoteLen*/ ){JASSERT(false);}
    void onDisconnect ( jalib::JReaderInterface* /*sock*/ ) { exit(0); };

    void onData ( jalib::JReaderInterface* sock ){
      static int stdinfd  = fileno(stdin);
      static int stdoutfd = fileno(stdout);
      char buf = *sock->buffer();
      log(buf);
      if(sock->socket().sockfd() == stdinfd)
        JASSERT(write(maximaFd, &buf, 1)==1);
      else
        JASSERT(write(stdoutfd, &buf, 1)==1);
    }

    void log(char c){
      static FILE* fd = fopen("maxima.log","w");
      JASSERT(fwrite(&c, 1,1, fd) == 1);
      fflush(fd);
    }

    int maximaFd;
  } forwarder;

  forwarder.maximaFd = forkopen(launchMaxima);
  jalib::JChunkReader maxima(forwarder.maximaFd, 1);
  jalib::JChunkReader petabricks(fileno(stdin),      1);
  forwarder.addDataSocket(&maxima);
  forwarder.addDataSocket(&petabricks);
  forwarder.monitorSockets();
  JASSERT(false);
}
#endif

static const char * const theInitCode = 
  "display2d : false $ "
  "prederror : false $ "
  "load(ineq) $ "
  "1"
;

extern FILE* maximain;
extern petabricks::FormulaListPtr readFormulaFromMaxima();

petabricks::MaximaWrapper& petabricks::MaximaWrapper::instance(){
  static MaximaWrapper inst;
  return inst;
}

petabricks::MaximaWrapper::MaximaWrapper()
  : _fd(-1)
  , _stackDepth(0)
{
#ifdef MAXIMA_LOG
  _fd = forkopen(&launchMaximaWithLogging);
#else
  _fd = forkopen(&launchMaxima);
#endif
  maximain = fdopen(_fd, "rw");
  runCommand(theInitCode);
}

petabricks::MaximaWrapper::~MaximaWrapper()
{
  maximain=NULL;
  close(_fd);
}

petabricks::FormulaListPtr petabricks::MaximaWrapper::runCommand(const char* cmd, int len){
  static const char endCommand[] = ";\n";
  JASSERT(write(_fd, cmd, len)==len)(cmd)(JASSERT_ERRNO);
  JASSERT(write(_fd, endCommand, sizeof endCommand-1)==sizeof endCommand-1)(cmd)(JASSERT_ERRNO);
  fsync(_fd);
//  JTRACE("Maxima query")(cmd);
  petabricks::FormulaListPtr result = readFormulaFromMaxima();
//   #ifdef DEBUG
//     JASSERT_STDERR << "     result = " << result << "\n";
//   #endif
  return result;
}

