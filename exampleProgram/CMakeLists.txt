CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(LOCAL_LIBS ../lib/)
SET(LOCAL_INC ../include/)

PROJECT(SemaphoresExamples)

SET(EXECUTABLE_OUTPUT_PATH ../bin)

SET( LIBS ${LIBS} pthread)
FIND_LIBRARY( LOGGER_LIBRARY NAMES logger
                PATHS ${LOCAL_LIBS} ${INSTALL_LIBS} )
SET( LIBS ${LIBS} ${LOGGER_LIBRARY})
FIND_LIBRARY( JPSEMAPHORES_LIBRARY NAMES JPSemaphores
                PATHS ${LOCAL_LIBS} ${INSTALL_LIBS} )
SET( LIBS ${LIBS} ${JPSEMAPHORES_LIBRARY})


SET(example_src exampleProgram.cpp) 
SET(example1_src exampleProgram1.cpp) 
ADD_EXECUTABLE( exampleProgram ${example_src})
ADD_EXECUTABLE( exampleProgram1 ${example1_src})
#
#find_library(logger REQUIRED)
#include_directories(${logger_INCLUDE_DIRS})
#set(LIBS ${LIBS} ${logger_LIBRARIES})
TARGET_LINK_LIBRARIES(exampleProgram ${LIBS} ${JPSEMAPHORES_LIBRARY} ${LOGGER_LIBRARY})
TARGET_LINK_LIBRARIES(exampleProgram1  ${LIBS} ${JPSEMAPHORES_LIBRARY} ${LOGGER_LIBRARY})

