CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(example_src exampleProgram.cpp) 
SET(example1_src exampleProgram1.cpp) 
ADD_EXECUTABLE( exampleProgram ${example_src})
ADD_EXECUTABLE( exampleProgram1 ${example1_src})
#
find_library(logger REQUIRED)
include_directories(${logger_INCLUDE_DIRS})
set(LIBS ${LIBS} ${logger_LIBRARIES})
TARGET_LINK_LIBRARIES(exampleProgram ${CPPJPLOGGER_LIB} pthread JPSemaphores)
TARGET_LINK_LIBRARIES(exampleProgram1  ${CPPJPLOGGER_LIB} pthread JPSemaphores )

