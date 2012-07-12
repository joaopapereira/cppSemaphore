
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET( lib_srcs libJPSemaphores.cpp )
include_directories( modules/include/ )
ADD_LIBRARY( JPSemaphores SHARED ${lib_srcs})

