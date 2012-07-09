CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/lib)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_HOME_DIRECTORY}/bin)

PROJECT(Semaphores)
INCLUDE_DIRECTORIES( include lib modules/include modules/lib)

ADD_SUBDIRECTORY( src lib )
ADD_SUBDIRECTORY( exampleProgram bin )
find_library( CPPJPLOGGER_LIB NAMES logger
		PATHS ${LOCAL_LIBS} )

find_library(logger REQUIRED)
include_directories(${logger_INCLUDE_DIRS})

#if( NOT CPPJPLOGGER_LIB )
#   EXECUTE_PROCESS( 
#                COMMAND cd modules/
#                COMMAND cmake -DLOCAL_LIBS=${LOCAL_LIBS} .
#		OUTPUT_VARIABLE _output
#                ERROR_VARIABLE  _error  )
#   message(AUTHOR_WARNING "entrou no normal \"${_output}\"\n\"${_error}\"")                  
#else( NOT CPPJPLOGGER_LIB ) 
#   message(AUTHOR_WARNING "foi para o else")                  
#endif( NOT CPPJPLOGGER_LIB )
   
