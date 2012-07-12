# find logger

IF(NOT(logger_LIBRARY AND logger_INCLUDE_DIR))
	# search for include and library path
	FIND_PATH(logger_INCLUDE_DIR  libJPLogger.h PATHS ${INSTALL_INCS} )
	FIND_LIBRARY(logger_LIBRARY logger PATHS ${INSTALL_LIBS} )

	IF(logger_INCLUDE_DIR AND logger_LIBRARY)
		SET(logger_FOUND TRUE)
		MESSAGE(STATUS "Found logger: ${logger_LIBRARY}")

	ELSE(logger_INCLUDE_DIR AND logger_LIBRARY)
		SET(logger_FOUND FALSE)
		MESSAGE(SEND_ERROR "Could NOT find logger")
	ENDIF(logger_INCLUDE_DIR AND logger_LIBRARY)
ENDIF( NOT ( logger_LIBRARY AND logger_INCLUDE_DIR) )
