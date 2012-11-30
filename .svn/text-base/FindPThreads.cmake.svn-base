# - Find the PThreads includes and libraries.
# The following variables are set if PThreads is found.  If PThreads is not
# found, PThreads_FOUND is set to false.
#  PThreads_FOUND        - True when the PThreads include directory is found.
#  PThreads_INCLUDE_DIRS - the path to where the PThreads include files are.
#  PThreads_LIBRARY_DIRS - The path to where the PThreads library files are.

# ----------------------------------------------------------------------------
# If you have installed PThreads in a non-standard location then you have three
# options. In the following comments, it is assumed that <Your Path>
# points to the root directory of the include directory of PThreads. e.g
# If you have put boost in C:\development\PThreads then <Your Path> is
# "C:/development/PThreads" and in this directory there will be two
# directories called "include" and "lib".
# 1) After CMake runs, set PThreads_INCLUDE_DIR to <Your Path>
# 2) Use CMAKE_INCLUDE_PATH to set a path to <Your Path>. This will allow FIND_PATH()
#    to locate PThreads_INCLUDE_DIR by utilizing the PATH_SUFFIXES option. e.g.
#    SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "<Your Path>")
# 3) Set an environment variable called ${PTHREADS_ROOT} that points to the root of where you have
#    installed PThreads, e.g. <Your Path>. It is assumed that there is at least a subdirectory called
#    include in this path.
#
# Usage:
# In your CMakeLists.txt file do something like this:
# ...
# # PThreads
# FIND_PACKAGE(PThreads)
# ...
# INCLUDE_DIRECTORIES(${PThreads_INCLUDE_DIRS})
# LINK_DIRECTORIES(${PThreads_LIBRARY_DIRS})
#

SET(PTHREADS_INCLUDE_PATH_DESCRIPTION "directory containing the PThreads include directory.")

SET(PTHREADS_DIR_MESSAGE "Set the PThreads_INCLUDE_DIR cmake cache entry to the ${PTHREADS_INCLUDE_PATH_DESCRIPTION}")

SET(PTHREADS_DIR_SEARCH $ENV{PTHREADS_ROOT})
IF(PTHREADS_DIR_SEARCH)
  FILE(TO_CMAKE_PATH ${PTHREADS_DIR_SEARCH} PTHREADS_DIR_SEARCH)
  SET(PTHREADS_DIR_SEARCH ${PTHREADS_DIR_SEARCH}/include)
ENDIF(PTHREADS_DIR_SEARCH)

IF(WIN32)
  SET(PTHREADS_DIR_SEARCH
    ${PTHREADS_DIR_SEARCH}
    $ENV{PTHREADS_ROOT}
    C:/pthreads
    D:/pthreads
  )
ENDIF(WIN32)

# Add in some path suffixes. These will have to be updated whenever a new PThreads version comes out.
SET(SUFFIX_FOR_PATH
 Pre-built.2/include
 Pre-built.1/include
 Pre-built/include
 pthreads.2
 pthreads.1
 pthreads
)

#
# Look for an installation.
#
FIND_PATH(PThreads_INCLUDE_DIR NAMES pthread.h PATH_SUFFIXES ${SUFFIX_FOR_PATH} PATHS

  # Look in other places.
  ${PTHREADS_DIR_SEARCH}

  # Help the user find it if we cannot.
  DOC "The ${PTHREADS_INCLUDE_PATH_DESCRIPTION}"
)

# Assume we didn't find it.
SET(PThreads_FOUND 0)

# Now try to get the include and library path.
IF(PThreads_INCLUDE_DIR)

  # Look for the PThreads library path.
  SET(PThreads_LIBRARY_DIR ${PThreads_INCLUDE_DIR})

  IF("${PThreads_LIBRARY_DIR}" MATCHES "/include$")
    # Strip off the trailing "/include" in the path.
    GET_FILENAME_COMPONENT(PThreads_LIBRARY_DIR ${PThreads_LIBRARY_DIR} PATH)
  ENDIF("${PThreads_LIBRARY_DIR}" MATCHES "/include$")

  IF(EXISTS "${PThreads_LIBRARY_DIR}/lib")
    SET (PThreads_LIBRARY_DIR ${PThreads_LIBRARY_DIR}/lib)
  ENDIF(EXISTS "${PThreads_LIBRARY_DIR}/lib")

  IF(EXISTS "${PThreads_INCLUDE_DIR}")
    SET(PThreads_INCLUDE_DIRS ${PThreads_INCLUDE_DIR})
    SET(PThreads_FOUND 1)
  ENDIF(EXISTS "${PThreads_INCLUDE_DIR}")

  IF(PThreads_LIBRARY_DIR AND EXISTS "${PThreads_LIBRARY_DIR}")
    SET(PThreads_LIBRARY_DIRS ${PThreads_LIBRARY_DIR})
  ENDIF(PThreads_LIBRARY_DIR AND EXISTS "${PThreads_LIBRARY_DIR}")
ENDIF(PThreads_INCLUDE_DIR)

IF(NOT PThreads_FOUND)
  IF(NOT PThreads_FIND_QUIETLY)
    MESSAGE(STATUS "PThreads was not found. ${PTHREADS_DIR_MESSAGE}")
  ELSE(NOT PThreads_FIND_QUIETLY)
    IF(PThreads_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "PThreads was not found. ${PTHREADS_DIR_MESSAGE}")
    ENDIF(PThreads_FIND_REQUIRED)
  ENDIF(NOT PThreads_FIND_QUIETLY)
ENDIF(NOT PThreads_FOUND)

