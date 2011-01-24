# FIXME: Caching of the result seems to be broken, causing cmake to re-search 
# for SmallChange every time it runs. Otto 20101229.

# FIXME: Rewrite this to be more standards compliant
# See http://www.cmake.org/cgi-bin/viewcvs.cgi/Modules/readme.txt?root=CMake&view=markup
# Look at FindVTK for an example of how to solve the location mess we have in SmallChange

# FIXME: Document. Returns SmallChange_INCLUDE_DIR, SmallChange_DEFINES, SmallChange_LIBRAR(Y|IES)
# Note: Due to limiting CMake support for Mac OS X, we cannot assume that SmallChange_INCLUDE_DIR
# is an actual path pointing to the actual header files (it usually points to the 
# framework itself), so don't use this to do anything fancy in client CMakeLists.txt files.

SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS True)

IF(USE_SIM_FIND)
  # FIXME: Experimental find mechanism. Should be tested on several platforms with several
  # configurations and someone extended before becomming the one and only thing. 20081105 larsm
  INCLUDE(SimFind)
  SIM_FIND(SmallChange RELEASELIBNAMES SmallChange1
                  DEBUGLIBNAMES SmallChange1d
           )
ELSE(USE_SIM_FIND)
  IF(NOT COINDIR)
    SET(COINDIR $ENV{COINDIR})
    IF(COINDIR)
      MESSAGE(STATUS "Setting COINDIR to \"${COINDIR}\" from environment variable")
    ENDIF(COINDIR)
  ENDIF(NOT COINDIR)
  
  SET(SMALLCHANGE_NAMES SmallChange1)
  SET(SMALLCHANGE_NAMES_DEBUG SmallChange1d)

  IF(COINDIR)
    # Look for SmallChange in environment variable COINDIR
    FIND_LIBRARY(SmallChange_LIBRARY_RELEASE NAMES ${SMALLCHANGE_NAMES} PATHS ${COINDIR} PATH_SUFFIXES src bin lib . NO_DEFAULT_PATH)
    FIND_LIBRARY(SmallChange_LIBRARY_DEBUG NAMES ${SMALLCHANGE_NAMES_DEBUG} PATHS ${COINDIR} PATH_SUFFIXES src bin lib . NO_DEFAULT_PATH)

    IF(SmallChange_LIBRARY_RELEASE AND NOT SmallChange_LIBRARY_DEBUG)
      SET(SmallChange_LIBRARY_DEBUG ${SmallChange_LIBRARY_RELEASE})
      SET(SmallChange_LIBRARY       ${SmallChange_LIBRARY_RELEASE})
      SET(SmallChange_LIBRARIES     ${SmallChange_LIBRARY_RELEASE})
    ENDIF()

    IF(SmallChange_LIBRARY_DEBUG AND NOT SmallChange_LIBRARY_RELEASE)
      SET(SmallChange_LIBRARY_RELEASE ${SmallChange_LIBRARY_DEBUG})
      SET(SmallChange_LIBRARY       ${SmallChange_LIBRARY_DEBUG})
      SET(SmallChange_LIBRARIES     ${SmallChange_LIBRARY_DEBUG})
    ENDIF()

    IF(SmallChange_LIBRARY_DEBUG AND SmallChange_LIBRARY_RELEASE)
      IF(CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
	#If the generator supports configuration types then set
	#optimized and debug libraries, or if the CMAKE_BUILD_TYPE has a value
	SET(SmallChange_LIBRARY optimized ${SmallChange_LIBRARY_RELEASE} debug ${SmallChange_LIBRARY_DEBUG})
      ELSE()
	#If there are no configuration types and CMAKE_BUILD_TYPE has no value
	#then just use the release libraries
	SET(SmallChange_LIBRARY ${SmallChange_LIBRARY_RELEASE})
      ENDIF()
      SET(SmallChange_LIBRARIES optimized ${SmallChange_LIBRARY_RELEASE} debug ${SmallChange_LIBRARY_DEBUG})
    ENDIF()

    SET(SmallChange_LIBRARY ${SmallChange_LIBRARY} CACHE FILEPATH "The SmallChange library")
    MARK_AS_ADVANCED(SmallChange_LIBRARY_RELEASE SmallChange_LIBRARY_DEBUG)


    IF (SmallChange_LIBRARY)
      SET(SmallChange_FOUND TRUE)
    ENDIF ()

    IF (SmallChange_FOUND)
      MESSAGE(STATUS "Found SmallChange" "${SmallChange_LIBRARY}")
    ELSE (SmallChange_FOUND)
      IF (SmallChange_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find SmallChange in ${COINDIR} - try changing the COINDIR environment variable.")
      ENDIF (SmallChange_FIND_REQUIRED)
    ENDIF (SmallChange_FOUND)

  ELSE(COINDIR)
    # pkgconfig supported?
    INCLUDE(FindPkgConfig)

    IF(PKG_CONFIG_FOUND)
      IF (NOT SmallChange_FIND_QUIETLY)
	MESSAGE(STATUS "Using pkg-config to locate SmallChange.")
      ENDIF(NOT SmallChange_FIND_QUIETLY)

      pkg_search_module(SmallChange SmallChange)
      IF(SmallChange_FOUND)
	SET(SmallChange_LIBRARY ${SmallChange_LIBRARIES} ${SmallChange_LDFLAGS})
      ENDIF(SmallChange_FOUND)
    ENDIF(PKG_CONFIG_FOUND)

    # Automatic find, if pkg-config fails
    IF(NOT SmallChange_FOUND)
      FIND_LIBRARY(SmallChange_LIBRARY NAMES ${SMALLCHANGE_NAMES})
      IF (SmallChange_LIBRARY)
	SET(SmallChange_FOUND TRUE)
      ENDIF (SmallChange_LIBRARY)
    ENDIF(NOT SmallChange_FOUND)


    # Process stuff
    IF (SmallChange_FOUND)
      MESSAGE(STATUS "Found SmallChange" "${SmallChange_LIBRARY}")
    ELSE (SmallChange_FOUND)
      IF (SmallChange_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find SmallChange. Try setting the COINDIR environment variable to the root of the SmallChange 3 installation directory.")
      ENDIF (SmallChange_FIND_REQUIRED)
    ENDIF (SmallChange_FOUND)
  ENDIF(COINDIR)

  # SmallChange_DEFINES - only on WIN32
  IF (SmallChange_FOUND AND WIN32)
    FIND_FILE(SmallChange_pc NAMES SmallChange.pc PATHS ${COINDIR}/ PATH_SUFFIXES . lib/pkgconfig/ NO_DEFAULT_PATH)
    MARK_AS_ADVANCED(SmallChange_pc)
    IF(EXISTS ${SmallChange_pc})
      FILE(READ ${SmallChange_pc} SmallChangePC)
      IF (${SmallChangePC} MATCHES SMALLCHANGE_DLL)
	MESSAGE(STATUS "Found SmallChange.pc with -DSMALLCHANGE_DLL")
	SET(SmallChange_DEFINES -DSMALLCHANGE_DLL)
      ELSE()
	MESSAGE(STATUS "Found SmallChange.pc with -DSMALLCHANGE_NOT_DLL")
	SET(SmallChange_DEFINES -DSMALLCHANGE_NOT_DLL)
      ENDIF()
    ELSE()
      IF(SMALLCHANGE_NOT_DLL)
	SET(SmallChange_DEFINES -DSMALLCHANGE_NOT_DLL)
      ELSEIF(NOT SMALLCHANGE_DLL)
	SET(SmallChange_DEFINES -DSMALLCHANGE_DLL)
	MESSAGE(STATUS "WARNING: Could not find SmallChange.pc, using -DSMALLCHANGE_DLL=1. Override or remove this warning using cmake -DSMALLCHANGE_NOT_DLL=1 or cmake -DSMALLCHANGE_DLL=1.")
      ENDIF(SMALLCHANGE_NOT_DLL)
    ENDIF()
  ENDIF()

ENDIF(USE_SIM_FIND)
