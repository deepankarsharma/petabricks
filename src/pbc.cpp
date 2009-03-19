/***************************************************************************
 *   Copyright (C) 2008 by Jason Ansel                                     *
 *   jansel@csail.mit.edu                                                  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <fstream>

#include "jthread.h"
#include "jrefcounted.h"
#include "jfilesystem.h"
#include "matrix.h"
#include "matrixoperations.h"
#include "maximawrapper.h"
#include "transform.h"
#include "codegenerator.h"
#include "jfilesystem.h"

#ifdef HAVE_CONFIG_H
#  include "config.h"
#  include "cxxconfig.h"
#endif

void callCxxCompiler(const std::string& src, const std::string& bin);
std::string cmdCxxCompiler(const std::string& src, const std::string& bin);


using namespace petabricks;


const static std::string thePetabricksHPath = jalib::Filesystem::FindHelperUtility("petabricks.h");
const static std::string theLibPetabricksPath = jalib::Filesystem::FindHelperUtility("libpetabricks.a");

TransformListPtr parsePbFile(const char* filename);


int main( int argc, const char ** argv){
  if(argc != 2){
    fprintf(stderr, PACKAGE " PetaBricks compiler (pbc) v" VERSION "\n");
    fprintf(stderr, "USAGE: %s filename.pbcc\n", argv[0]);
    return 1;
  }
  std::string input = argv[1];
  std::string outputBin = jalib::Filesystem::Basename(input);
  std::string outputCode = outputBin + ".cpp";
  std::string outputInfo = outputBin + ".info";

  CodeGenerator::theFilePrefix() << "// Generated by " PACKAGE " PetaBricks compiler (pbc) v" VERSION "\n";
  CodeGenerator::theFilePrefix() << "// Compile with:\n";
  CodeGenerator::theFilePrefix() << "// " << cmdCxxCompiler(outputCode, outputBin) << "\n\n";
  CodeGenerator::theFilePrefix() << "#include \""+thePetabricksHPath+"\"\n";
  #ifdef SHORT_TYPE_NAMES
  CodeGenerator::theFilePrefix() <<"using namespace petabricks;\n\n";
  #endif

  TransformListPtr t = parsePbFile(input.c_str());

  for(TransformList::iterator i=t->begin(); i!=t->end(); ++i){
    JTRACE("initializing")(input)(outputCode)((*i)->name());
    (*i)->initialize();
    #ifdef DEBUG
    (*i)->print(std::cout);
    #endif
  }
  
  for(TransformList::iterator i=t->begin(); i!=t->end(); ++i){
    JTRACE("compiling")(input)(outputCode)((*i)->name());
    (*i)->compile();
  }

  std::ofstream of(outputCode.c_str());
  std::ofstream infofile(outputInfo.c_str());
  MainCodeGenerator o;  
  for(TransformList::iterator i=t->begin(); i!=t->end(); ++i){
    JTRACE("generating")(input)(outputCode)((*i)->name());
    (*i)->generateCode(o);
  }
  
  o.comment("Program main routine");
  std::string args[] = {"int argc", "const char** argv"};
  o.beginFunc("int", "main", std::vector<std::string>(args, args+2));
  o.write("petabricks::PetabricksRuntime runtime(argc, argv, "+t->back()->name()+"_main);");
  for(TransformList::iterator i=t->begin(); i!=t->end(); ++i){
    (*i)->registerMainInterface(o);
  }
  o.write("return runtime.runMain(argc,argv);");
  o.endFunc();
  
  o.outputFileTo(of);
  of.flush();
  of.close();
  o.cg().dumpTo(infofile);
  infofile.flush();
  infofile.close();
  callCxxCompiler(outputCode, outputBin);

  JTRACE("done")(input)(outputInfo)(outputCode)(outputBin);
  return 0;
}

std::string cmdCxxCompiler(const std::string& src, const std::string& bin){
 return CXX " " CXXFLAGS " " DEFS " -o " + bin + " " + src + " " + theLibPetabricksPath + " " LIBS;
}

void callCxxCompiler(const std::string& src, const std::string& bin){
  std::string cmd = cmdCxxCompiler(src,bin);
  JTRACE("Running g++")(cmd);
  std::cout << cmd << std::endl; 
  int rv = system(cmd.c_str());
  JASSERT(rv==0)(rv)(cmd).Text("g++ call failed");
}
