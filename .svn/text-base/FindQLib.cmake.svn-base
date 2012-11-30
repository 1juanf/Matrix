# Find the UF installation or build tree.
# If QLib is not found, QLib_FOUND is set to false.
# The following variables are set if QLib is found.
#  QLib_FOUND         - Set to true when QLib is found.
#  QLib_USE_FILE      - CMake file to use QLib.
#  QLib_MAJOR_VERSION - The QLib major version number.
#  QLib_MINOR_VERSION - The QLib minor version number
#                       (odd non-release).
#  QLib_BUILD_VERSION - The QLib patch level
#                       (meaningless for odd minor).
#  QLib_INCLUDE_DIRS  - Include directories for QLib
#  QLib_LIBRARY_DIRS  - Link directories for QLib libraries
# The following cache entries must be set by the user to locate QLib:
#  QLib_DIR  - The directory where QLib was installed
#				eg c:\program files\QLib
#				it is the directory containing subdirs (include, bin, lib, CMakeFiles)
#			   This can also be the root of the build tree - the dir where the QLib makefiles/project files exist
#				eg c:\build\QLib\

# Construct consitent error messages for use below.
SET(QLib_DIR_DESCRIPTION "QLib installation directory - this is either the root of the build tree, or the installed location")
SET(QLib_DIR_MESSAGE "QLib not found.  Set the QLib_DIR cmake cache entry to the ${QLib_DIR_DESCRIPTION}")

#If the location is not already known, then search.
IF ( NOT QLib_DIR )
  # Get the system search path as a list.
  IF(UNIX)
    STRING(REGEX MATCHALL "[^:]+" QLib_DIR_SEARCH1 "$ENV{PATH}")
  ELSE(UNIX)
    STRING(REGEX REPLACE "\\\\" "/" QLib_DIR_SEARCH1 "$ENV{PATH}")
  ENDIF(UNIX)
  IF ( WIN32 )
    # Assume this path exists.
    SET ( QLib_DIR_SEARCH1
      ${QLib_DIR_SEARCH1}
      "C:/Program Files/QLib"
    )
  ENDIF ( WIN32 )
  STRING(REGEX REPLACE "/;" ";" QLib_DIR_SEARCH2 "${QLib_DIR_SEARCH1}")

  SET ( QLib_DIR_SEARCH "${QLib_DIR_SEARCH2}" } )

  #
  # Look for an installation or build tree.
  #
  FIND_PATH(QLib_DIR NAMES CMakeFiles/UseQLib.cmake PATH_SUFFIXES ${SUFFIX_FOR_PATH} PATHS

     # Look for an environment variable QLib_DIR.
      $ENV{QLib_DIR}

      # Look in places relative to the system executable search path.
      ${QLib_DIR_SEARCH}

      # Look in standard UNIX install locations.
      /usr/local/lib
      /usr/lib

      # Help the user find it if we cannot.
      DOC "The ${QLib_DIR_DESCRIPTION}"
  )
ENDIF ( NOT QLib_DIR )

# If QLib was found, load the configuration file to get the rest of the
# settings.
IF(QLib_DIR)
  # Make sure the QLibConfig.cmake file exists in the directory provided.
  IF(EXISTS ${QLib_DIR}/CMakeFiles/QLibConfig.cmake)
    # We found QLib.  Load the settings.
    SET(QLib_FOUND 1)
    INCLUDE(${QLib_DIR}/CMakeFiles/QLibConfig.cmake)
  ENDIF(EXISTS ${QLib_DIR}/CMakeFiles/QLibConfig.cmake)
ELSE(QLib_DIR)
  # We did not find QLib_.
  SET(QLib_FOUND 0)
ENDIF(QLib_DIR)

IF ( QLib_FOUND )
  IF ( EXISTS ${QLib_USE_FILE} )
    INCLUDE(${QLib_USE_FILE})
    IF ( EXISTS ${QLib_BUILD_SETTINGS_FILE} )
      # CMake 2.8.x and greater do not need to include these build settings files. (CMAKE_BUILD_SETTINGS_EXPORT is deprecated)
      IF( ${CMAKE_MAJOR_VERSION} LESS "2" OR ( ${CMAKE_MAJOR_VERSION} EQUAL "2" AND ${CMAKE_MINOR_VERSION} LESS "8" ) )
      	INCLUDE(${QLib_BUILD_SETTINGS_FILE})
      ENDIF( ${CMAKE_MAJOR_VERSION} LESS "2" OR ( ${CMAKE_MAJOR_VERSION} EQUAL "2" AND ${CMAKE_MINOR_VERSION} LESS "8" ) )
    ELSE ( EXISTS ${QLib_BUILD_SETTINGS_FILE} )
      SET(QLib_FOUND 0)
    ENDIF ( EXISTS ${QLib_BUILD_SETTINGS_FILE} )
  ELSE ( EXISTS ${QLib_USE_FILE} )
    SET(QLib_FOUND 0)
  ENDIF ( EXISTS ${QLib_USE_FILE} )
ENDIF ( QLib_FOUND )

IF( NOT QLib_FOUND )
  MESSAGE(FATAL_ERROR ${QLib_DIR_MESSAGE})
ENDIF( NOT QLib_FOUND )

