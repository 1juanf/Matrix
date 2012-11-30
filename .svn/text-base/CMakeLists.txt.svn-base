SET( PROJECT_NAME "Matrix" )
PROJECT(${PROJECT_NAME})

#-----------------------------------------------------------------------------
# Find WxWidgets.

SET(wxWidgets_USE_LIBS base core adv aui gl )
FIND_PACKAGE(wxWidgets) # this is part of cmake
IF(wxWidgets_FOUND)
  INCLUDE(${wxWidgets_USE_FILE})
  INCLUDE_DIRECTORIES(${wxWidgets_INCLUDE_DIRS})
  LINK_DIRECTORIES(${wxWidgets_LIB_DIR})
ENDIF(wxWidgets_FOUND)

#-----------------------------------------------------------------------------
# QLib
#FIND_PACKAGE(QLib REQUIRED)
INCLUDE(FindQLib.cmake REQUIRED)

#-----------------------------------------------------------------------------
  # PThreads
  FIND_PACKAGE(Threads)
  IF(NOT CMAKE_USE_PTHREADS_INIT)
    SET ( PThreads_DIR ${PROJECT_SOURCE_DIR} )
    INCLUDE(FindPThreads.cmake REQUIRED)
    IF ( EXISTS ${PThreads_INCLUDE_DIRS} )
      INCLUDE_DIRECTORIES(${PThreads_INCLUDE_DIRS})
    ENDIF ( EXISTS ${PThreads_INCLUDE_DIRS} )
    IF ( EXISTS ${PThreads_LIBRARY_DIRS} )
      LINK_DIRECTORIES(${PThreads_LIBRARY_DIRS})
    ENDIF ( EXISTS ${PThreads_LIBRARY_DIRS} )
  ENDIF(NOT CMAKE_USE_PTHREADS_INIT)


##############################################################################
# EXE1
##############################################################################

	#-----------------------------------------------------------------------------
	# Include the source files.
	FILE( GLOB EXE1_ProjectSourceCore	./Core/*.cpp	./Core/*.h )
	FILE( GLOB EXE1_ProjectSourceWx		./Wx/*.cpp	./Wx/*.h )
	SOURCE_GROUP( "Core"	FILES	${EXE1_ProjectSourceCore} )
	SOURCE_GROUP( "Wx"		FILES	${EXE1_ProjectSourceWx} )
	SET(	EXE1_ProjectSource
			${EXE1_ProjectSourceCore}
			${EXE1_ProjectSourceWx}
		)
	#-----------------------------------------------------------------------------

	#-----------------------------------------------------------------------------
	# Add the executable, pointing to the project source and headers.
	# On Win32, point to pthreadVC2.lib and instruct CMake how to manage the
	# executable properly.
	IF(WIN32)
		ADD_EXECUTABLE( ${PROJECT_NAME} WIN32 ${EXE1_ProjectSource} )
		TARGET_LINK_LIBRARIES ( ${PROJECT_NAME} pthreadVC2.lib )
	ELSE(WIN32)
		ADD_EXECUTABLE( ${PROJECT_NAME} ${EXE1_ProjectSource} )
	ENDIF(WIN32)
	#-----------------------------------------------------------------------------

	#-----------------------------------------------------------------------------
	# Link to required QLib and wxWidgets libraries.
	TARGET_LINK_LIBRARIES	(	${PROJECT_NAME}
								OpenGL32.lib
								GLu32.lib
								GLaux.lib
								debug QBytestreams-d
								optimized QBytestreams
								debug QLogging-d
								optimized QLogging
								debug QDataStructures-d
								optimized QDataStructures
								debug QUtilities-d
								optimized QUtilities
								debug QTiming-d
								optimized QTiming
								debug QExceptions-d
								optimized QExceptions
								debug QThreads-d
								optimized QThreads
								debug QPatterns-d
								optimized QPatterns
								${wxWidgets_LIBRARIES}
								debug QGUI-d
								optimized QGUI
							)
	#-----------------------------------------------------------------------------


