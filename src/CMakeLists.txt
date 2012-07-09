
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET( lib_srcs libJPSemaphores.cpp )

ADD_LIBRARY( JPSemaphores SHARED ${lib_srcs})

#install (TARGETS logger DESTINATION lib/)
#install (FILES include/*.h DESTINATION include/)
#INSTALL(TARGETS logger
#        LIBRARY DESTINATION lib
#        ARCHIVE DESTINATION lib
#      )
#SET(CMAKE_INSTALL_LIBDIR lib CACHE PATH "Output directory for libraries")
#install(TARGETS logger DESTINATION ${CMAKE_INSTALL_LIBDIR})
