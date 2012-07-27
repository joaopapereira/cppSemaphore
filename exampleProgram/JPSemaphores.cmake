# find JPSemaphore

IF(NOT(JPSemaphore_LIBRARY AND JPSemaphore_INCLUDE_DIR))
	# search for include and library path
	FIND_PATH(JPSemaphore_INCLUDE_DIR  libJPSemaphores.h PATHS ${LOCAL_INC} )
	FIND_LIBRARY(JPSemaphore_LIBRARY JPSemaphores PATHS ${LOCAL_LIBS} )

	IF(JPSemaphore_INCLUDE_DIR AND JPSemaphore_LIBRARY)
		SET(JPSemaphore_FOUND TRUE)
		MESSAGE(STATUS "Found JPSemaphore: ${JPSemaphore_LIBRARY}")

	ELSE(JPSemaphore_INCLUDE_DIR AND JPSemaphore_LIBRARY)
		SET(JPSemaphore_FOUND FALSE)
		MESSAGE(SEND_ERROR "Could NOT find JPSemaphore")
	ENDIF(JPSemaphore_INCLUDE_DIR AND JPSemaphore_LIBRARY)
ENDIF( NOT ( JPSemaphore_LIBRARY AND JPSemaphore_INCLUDE_DIR) )
