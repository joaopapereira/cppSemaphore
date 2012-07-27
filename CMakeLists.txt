CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

IF( DEFINED ENV{INSTALL_LIB_DIR} )
   SET(INSTALL_LIBS $ENV{INSTALL_LIB_DIR}/ )
ELSE()
   SET(INSTALL_LIBS ${CMAKE_HOME_DIRECTORY}/lib )
ENDIF()
IF( DEFINED ENV{INSTALL_INC_DIR} )
   SET(INSTALL_INCS $ENV{INSTALL_INC_DIR}/ )
ELSE()
   SET(INSTALL_INCS ${CMAKE_HOME_DIRECTORY}/include )
ENDIF()

IF( EXISTS ${INSTALL_LIBS}/libJPSemaphores.so )
	return()
ENDIF()


SET(LIBRARY_OUTPUT_PATH .)
SET(EXECUTABLE_OUTPUT_PATH .)

PROJECT(Semaphores)
INCLUDE_DIRECTORIES( include lib ${INSTALL_LIBS} ${INSTALL_INCS})

ADD_SUBDIRECTORY( src lib )
#ADD_SUBDIRECTORY( exampleProgram bin )
#####################################
# Search for needed lib
#####################################
FIND_LIBRARY( CPPJPLOGGER_LIB NAMES logger
		PATHS ${LOCAL_LIBS} ${INSTALL_LIBS} )

find_library(logger REQUIRED)
include_directories(${logger_INCLUDE_DIRS})

#####################################
# Instalation section
#####################################
INSTALL( FILES include/libJPSemaphores.hpp
         DESTINATION ${INSTALL_INCS} )

INSTALL( FILES lib/libJPSemaphores.so
         DESTINATION ${INSTALL_LIBS} )

#####################################
# Others
#####################################
IF( UNIX )
   ADD_CUSTOM_TARGET( distclean @@echo cleaning for source distribution)
  SET(DISTCLEANED
   cmake.depends
   cmake.check_depends
   CMakeCache.txt
   cmake.check_cache
   Makefile
   core core.*
   gmon.out
   *~
   lib
   CMakeFiles
   bin
   install_*
   cmake_install.cmake 
  )
  
  ADD_CUSTOM_COMMAND(
    DEPENDS clean
    COMMENT "distribution clean"
    COMMAND rm
    ARGS    -Rf CMakeTmp ${DISTCLEANED}
    TARGET  distclean
  )

ENDIF( UNIX )

