# FIXME: Caching of the result seems to be broken, causing cmake to re-search 
# for SIMVoleon every time it runs. Otto 20101229.

# FIXME: Rewrite this to be more standards compliant
# See http://www.cmake.org/cgi-bin/viewcvs.cgi/Modules/readme.txt?root=CMake&view=markup
# Look at FindVTK for an example of how to solve the location mess we have in SIMVoleon

# FIXME: Document. Returns SIMVoleon_INCLUDE_DIR, SIMVoleon_DEFINES, SIMVoleon_LIBRAR(Y|IES)
# Note: Due to limiting CMake support for Mac OS X, we cannot assume that SIMVoleon_INCLUDE_DIR
# is an actual path pointing to the actual header files (it usually points to the 
# framework itself), so don't use this to do anything fancy in client CMakeLists.txt files.

SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS True)

IF(USE_SIM_FIND)
  # FIXME: Experimental find mechanism. Should be tested on several platforms with several
  # configurations and someone extended before becoming the one and only thing. 20081105 larsm
  INCLUDE(SimFind)
  SIM_FIND(SIMVoleon RELEASELIBNAMES simvoleon simvoleon2
                  DEBUGLIBNAMES simvoleond simvoleon2d
                  INCLUDEFILE VolumeViz/details/SoVolumeDetail.h)
ELSE(USE_SIM_FIND)
  IF(NOT COINDIR)
    SET(COINDIR $ENV{COINDIR})
    IF(COINDIR)
      MESSAGE(STATUS "Setting COINDIR to \"${COINDIR}\" from environment variable")
    ENDIF(COINDIR)
  ENDIF(NOT COINDIR)
  
  SET(SIMVOLEON_NAMES simvoleon simvoleon2)
  SET(SIMVOLEON_NAMES_DEBUG simvoleond simvoleon2d)

  IF(COINDIR)
    # Look for Coin in environment variable COINDIR
    FIND_LIBRARY(SIMVoleon_LIBRARY_RELEASE NAMES ${SIMVOLEON_NAMES} PATHS ${COINDIR} PATH_SUFFIXES src bin lib . NO_DEFAULT_PATH)
    FIND_LIBRARY(SIMVoleon_LIBRARY_DEBUG NAMES ${SIMVOLEON_NAMES_DEBUG} PATHS ${COINDIR} PATH_SUFFIXES src bin lib . NO_DEFAULT_PATH)

    IF(SIMVoleon_LIBRARY_RELEASE AND NOT SIMVoleon_LIBRARY_DEBUG)
      SET(SIMVoleon_LIBRARY_DEBUG ${SIMVoleon_LIBRARY_RELEASE})
      SET(SIMVoleon_LIBRARY       ${SIMVoleon_LIBRARY_RELEASE})
      SET(SIMVoleon_LIBRARIES     ${SIMVoleon_LIBRARY_RELEASE})
    ENDIF()

    IF(SIMVoleon_LIBRARY_DEBUG AND NOT SIMVoleon_LIBRARY_RELEASE)
      SET(SIMVoleon_LIBRARY_RELEASE ${SIMVoleon_LIBRARY_DEBUG})
      SET(SIMVoleon_LIBRARY       ${SIMVoleon_LIBRARY_DEBUG})
      SET(SIMVoleon_LIBRARIES     ${SIMVoleon_LIBRARY_DEBUG})
    ENDIF()

    IF(SIMVoleon_LIBRARY_DEBUG AND SIMVoleon_LIBRARY_RELEASE)
      IF(CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
	#If the generator supports configuration types then set
	#optimized and debug libraries, or if the CMAKE_BUILD_TYPE has a value
	SET(SIMVoleon_LIBRARY optimized ${SIMVoleon_LIBRARY_RELEASE} debug ${SIMVoleon_LIBRARY_DEBUG})
      ELSE()
	#If there are no configuration types and CMAKE_BUILD_TYPE has no value
	#then just use the release libraries
	SET(SIMVoleon_LIBRARY ${SIMVoleon_LIBRARY_RELEASE})
      ENDIF()
      SET(SIMVoleon_LIBRARIES optimized ${SIMVoleon_LIBRARY_RELEASE} debug ${SIMVoleon_LIBRARY_DEBUG})
    ENDIF()

    SET(SIMVoleon_LIBRARY ${SIMVoleon_LIBRARY} CACHE FILEPATH "The SIMVoleon library")
    MARK_AS_ADVANCED(SIMVoleon_LIBRARY_RELEASE SIMVoleon_LIBRARY_DEBUG)

    FIND_PATH(SIMVoleon_INCLUDE_DIR VolumeViz/details/SoVolumeDetail.h PATHS ${COINDIR} PATH_SUFFIXES include . NO_DEFAULT_PATH)

    IF (SIMVoleon_INCLUDE_DIR AND SIMVoleon_LIBRARY)
      SET(SIMVoleon_FOUND TRUE)
    ENDIF ()

    IF (SIMVoleon_FOUND)
      MESSAGE(STATUS "Found SIMVoleon" "${SIMVoleon_LIBRARY}")
    ELSE (SIMVoleon_FOUND)
      IF (SIMVoleon_FIND_REQUIRED)
        MESSAGE(STATUS "Could not find SIMVoleon in ${COINDIR} - try changing the COINDIR environment variable.")
      ENDIF (SIMVoleon_FIND_REQUIRED)
    ENDIF (SIMVoleon_FOUND)

  ELSE(COINDIR)
    # pkgconfig supported?
    INCLUDE(FindPkgConfig)

    IF(PKG_CONFIG_FOUND)
      IF (NOT SIMVoleon_FIND_QUIETLY)
	MESSAGE(STATUS "Using pkg-config to locate SIMVoleon.")
      ENDIF(NOT SIMVoleon_FIND_QUIETLY)

      pkg_search_module(SIMVoleon SIMVoleon)
      IF(SIMVoleon_FOUND)
	SET(SIMVoleon_LIBRARY ${SIMVoleon_LIBRARIES} ${SIMVoleon_LDFLAGS})
	SET(SIMVoleon_INCLUDE_DIR ${SIMVoleon_INCLUDE_DIRS})
        MESSAGE(STATUS "Found SIMVoleon" "${SIMVoleon_LIBRARY}")
      ENDIF(SIMVoleon_FOUND)
    ENDIF(PKG_CONFIG_FOUND)

    # Automatic find, if pkg-config fails
    IF(NOT SIMVoleon_FOUND)
      FIND_PATH(SIMVoleon_INCLUDE_DIR VolumeViz/details/SoVolumeDetail.h)

      FIND_LIBRARY(SIMVoleon_LIBRARY NAMES ${SIMVOLEON_NAMES})

      IF (SIMVoleon_INCLUDE_DIR AND SIMVoleon_LIBRARY)
	SET(SIMVoleon_FOUND TRUE)
      ENDIF (SIMVoleon_INCLUDE_DIR AND SIMVoleon_LIBRARY)
    ENDIF(NOT SIMVoleon_FOUND)


    # Process stuff
    IF (SIMVoleon_FOUND)
      MESSAGE(STATUS "Found SIMVoleon" "${SIMVoleon_LIBRARY}")
    ELSE (SIMVoleon_FOUND)
      IF (SIMVoleon_FIND_REQUIRED)
        MESSAGE(STATUS "Could not find SIMVoleon. Try setting the COINDIR environment variable to the root of the Coin 3 installation directory.")
      ENDIF (SIMVoleon_FIND_REQUIRED)
    ENDIF (SIMVoleon_FOUND)
  ENDIF(COINDIR)

  # SIMVoleon_DEFINES - only on WIN32
  IF (SIMVoleon_FOUND AND WIN32)
    FIND_FILE(SIMVoleon_pc NAMES SIMVoleon.pc PATHS ${SIMVoleon_INCLUDE_DIR}/../ PATH_SUFFIXES . lib/pkgconfig/ NO_DEFAULT_PATH)
    MARK_AS_ADVANCED(SIMVoleon_pc)
    IF(EXISTS ${SIMVoleon_pc})
      FILE(READ ${SIMVoleon_pc} SIMVoleonPC)
      IF (${SIMVoleonPC} MATCHES SIMVOLEON_DLL)
	MESSAGE(STATUS "Found SIMVoleon.pc with -DSIMVOLEON_DLL")
	SET(SIMVoleon_DEFINES -DSIMVOLEON_DLL)
      ELSE()
	MESSAGE(STATUS "Found SIMVoleon.pc with -DSIMVOLEON_NOT_DLL")
	SET(SIMVoleon_DEFINES -DSIMVOLEON_NOT_DLL)
      ENDIF()
    ELSE()
      IF(SIMVOLEON_NOT_DLL)
	SET(SIMVoleon_DEFINES -DSIMVOLEON_NOT_DLL)
      ELSEIF(NOT SIMVOLEON_DLL)
	SET(SIMVoleon_DEFINES -DSIMVOLEON_DLL)
	MESSAGE(STATUS "WARNING: Could not find SIMVoleon.pc, using -DSIMVOLEON_DLL=1. Override or remove this warning using cmake -DSIMVOLEON_NOT_DLL=1 or cmake -DSIMVOLEON_DLL=1.")
      ENDIF(SIMVOLEON_NOT_DLL)
    ENDIF()
  ENDIF()

ENDIF(USE_SIM_FIND)

