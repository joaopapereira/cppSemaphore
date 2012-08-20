/*
 ============================================================================
 Name        : exampleProgram.c
 Author      : Joao Pereira
 Version     :
 Copyright   : This library is creating under the GPL license
 Description : Uses shared library to print greeting
               To run the resulting executable the LD_LIBRARY_PATH must be
               set to ${project_loc}/libJPSemaphores/.libs
               Alternatively, libtool creates a wrapper shell script in the
               build directory of this program which can be used to run it.
               Here the script will be called exampleProgram.
 ============================================================================
 */
#include "libJPLogger.hpp"
#include "libJPSemaphores.hpp"
#include <unistd.h>
#include <iostream>

#define MAX_PROCESS 5
using namespace jpCppLibs;

int main(void) {
  Logger log("/tmp/test.log");
  log.setLogLvl("SEM", M_LOG_MIN , M_LOG_ALLLVL);
  OneInstanceLogger::instance()->copyLoggerDef(&log);
  JPSemaphore sem(1,MAX_PROCESS);
  pid_t allPids[MAX_PROCESS];
  pid_t actualPid;
  int num = 0;
  for( num = 0 ; num < MAX_PROCESS ; num++) sem.down();

  num = 0;
  while( num < MAX_PROCESS){
	  actualPid = fork();
	  if( 0 == actualPid )
		  break;
	  allPids[ num ] = actualPid;
	  num++;
  }
  if( 0 == actualPid ){//child process
	  std::cout << "[Child] sleep for 2 seconds" <<std::endl;
	  sleep(2);
	  std::cout << "[Child] up on sem" <<std::endl;
	  sem.up();
	  std::cout << "[Child] And i will die" <<std::endl;
  }else {// parent

	  num = 0;
	  std::cout << "[Parent] down on sem" <<std::endl;
	  while( num < MAX_PROCESS ){
		  std::cout << "[Parent] still need " << (MAX_PROCESS - num) << "childs to die" <<std::endl;
		  sem.down();
		  num++;
	  }
	  std::cout << "[Parent] someone release the sem going to die" <<std::endl;



  }

  OneInstanceLogger::instance()->log("Ended APP","SEM",M_LOG_NRM,M_LOG_DBG);
  return 0;
}
