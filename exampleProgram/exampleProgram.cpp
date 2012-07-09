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
#include "libJPLogger.h"
#include "libJPSemaphores.hpp"
#include <unistd.h>
#include <iostream>


int main(void) {
  Logger log("/tmp/test.log");
  log.setLogLvl("SEM", M_LOG_MIN , M_LOG_ALLLVL);
  OneInstanceLogger::instance()->copyLoggerDef(&log);
  JPBinSemaphore sem;

  pid_t pID = fork();
  if( 0 == pID ){//child process
	  std::cout << "[Child] down on sem" <<std::endl;
	  sem.down();
	  sleep(2);
	  std::cout << "[Child]Now i will send it up" <<std::endl;
	  sem.up();
	  std::cout << "[Child] And i will die" <<std::endl;
  }else {// parent

	  std::cout << "[Parent] going to sleep" <<std::endl;
	  sleep(1);
	  std::cout << "[Parent] down on sem" <<std::endl;
	  sem.down();
	  std::cout << "[Parent] someone release the sem going to die" <<std::endl;
  }

  OneInstanceLogger::instance()->log("Ended APP","SEM",M_LOG_NRM,M_LOG_DBG);
  return 0;
}
