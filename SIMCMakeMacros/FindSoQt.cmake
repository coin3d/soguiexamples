# FIXME: Caching of the result seems to be broken, causing cmake to re-search 
# for SoQt every time it runs. Otto 20101229.

# FIXME: Rewrite this to be more standards compliant
# See http://www.cmake.org/cgi-bin/viewcvs.cgi/Modules/readme.txt?root=CMake&view=markup
# Look at FindVTK for an example of how to solve the location mess we have in SoQt

# FIXME: Document. Returns SoQt_INCLUDE_DIR, SoQt_DEFINES, SoQt_LIBRAR(Y|IES)
# Note: Due to limiting CMake support for Mac OS X, we cannot assume that SoQt_INCLUDE_DIR
# is an actual path pointing to the actual header files (it usually points to the 
# framework itself), so don't use this to do anything fancy in client CMakeLists.txt files.

SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS True)

IF(USE_SIM_FIND)
  # FIXME: Experimental find mechanism. Should be tested on several platforms with several
  # configurations and someone extended before becomming the one and only thing. 20081105 larsm
  INCLUDE(SimFind)
  SIM_FIND(SoQt RELEASELIBNAMES SoQt soqt1
                  DEBUGLIBNAMES SoQtd soqt1d
                  INCLUDEFILE Inventor/Qt/SoQt.h)
ELSE(USE_SIM_FIND)
  IF(NOT COINDIR)
    SET(COINDIR $ENV{COINDIR})
    IF(COINDIR)
      MESSAGE(STATUS "Setting COINDIR to \"${COINDIR}\" from environment variable")
    ENDIF(COINDIR)
  ENDIF(NOT COINDIR)
  
  SET(SOQT_NAMES SoQt soqt1)
  SET(SOQT_NAMES_DEBUG SoQtd soqt1d)

  IF(COINDIR)
    # Look for Coin in environment variable COINDIR
    FIND_LIBRARY(SoQt_LIBRARY_RELEASE NAMES ${SOQT_NAMES} PATHS ${COINDIR} PATH_SUFFIXES src bin lib . NO_DEFAULT_PATH)
    FIND_LIBRARY(SoQt_LIBRARY_DEBUG NAMES ${SOQT_NAMES_DEBUG} PATHS ${COINDIR} PATH_SUFFIXES src bin lib . NO_DEFAULT_PATH)

    IF(SoQt_LIBRARY_RELEASE AND NOT SoQt_LIBRARY_DEBUG)
      SET(SoQt_LIBRARY_DEBUG ${SoQt_LIBRARY_RELEASE})
      SET(SoQt_LIBRARY       ${SoQt_LIBRARY_RELEASE})
      SET(SoQt_LIBRARIES     ${SoQt_LIBRARY_RELEASE})
    ENDIF()

    IF(SoQt_LIBRARY_DEBUG AND NOT SoQt_LIBRARY_RELEASE)
      SET(SoQt_LIBRARY_RELEASE ${SoQt_LIBRARY_DEBUG})
      SET(SoQt_LIBRARY       ${SoQt_LIBRARY_DEBUG})
      SET(SoQt_LIBRARIES     ${SoQt_LIBRARY_DEBUG})
    ENDIF()

    IF(SoQt_LIBRARY_DEBUG AND SoQt_LIBRARY_RELEASE)
      IF(CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE)
	#If the generator supports configuration types then set
	#optimized and debug libraries, or if the CMAKE_BUILD_TYPE has a value
	SET(SoQt_LIBRARY optimized ${SoQt_LIBRARY_RELEASE} debug ${SoQt_LIBRARY_DEBUG})
      ELSE()
	#If there are no configuration types and CMAKE_BUILD_TYPE has no value
	#then just use the release libraries
	SET(SoQt_LIBRARY ${SoQt_LIBRARY_RELEASE})
      ENDIF()
      SET(SoQt_LIBRARIES optimized ${SoQt_LIBRARY_RELEASE} debug ${SoQt_LIBRARY_DEBUG})
    ENDIF()

    SET(SoQt_LIBRARY ${SoQt_LIBRARY} CACHE FILEPATH "The SoQt library")
    MARK_AS_ADVANCED(SoQt_LIBRARY_RELEASE SoQt_LIBRARY_DEBUG)

    FIND_PATH(SoQt_INCLUDE_DIR Inventor/Qt/SoQt.h PATHS ${COINDIR} PATH_SUFFIXES include . NO_DEFAULT_PATH)

    IF (SoQt_INCLUDE_DIR AND SoQt_LIBRARY)
      SET(SoQt_FOUND TRUE)
    ENDIF ()

    IF (SoQt_FOUND)
      MESSAGE(STATUS "Found SoQt" "${SoQt_LIBRARY}")
    ELSE (SoQt_FOUND)
      IF (SoQt_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find SoQt in ${COINDIR} - try changing the COINDIR environment variable.")
      ENDIF (SoQt_FIND_REQUIRED)
    ENDIF (SoQt_FOUND)

  ELSE(COINDIR)
    # pkgconfig supported?
    INCLUDE(FindPkgConfig)

    IF(PKG_CONFIG_FOUND)
      IF (NOT SoQt_FIND_QUIETLY)
	MESSAGE(STATUS "Using pkg-config to locate SoQt.")
      ENDIF(NOT SoQt_FIND_QUIETLY)

      pkg_search_module(SoQt SoQt)
      IF(SoQt_FOUND)
	SET(SoQt_LIBRARY ${SoQt_LIBRARIES} ${SoQt_LDFLAGS})
	SET(SoQt_INCLUDE_DIR ${SoQt_INCLUDE_DIRS})
        MESSAGE(STATUS "Found SoQt" "${SoQt_LIBRARY}")
      ENDIF(SoQt_FOUND)
    ENDIF(PKG_CONFIG_FOUND)

    # Automatic find, if pkg-config fails
    IF(NOT SoQt_FOUND)
      FIND_PATH(SoQt_INCLUDE_DIR Inventor/Qt/SoQt.h)

      FIND_LIBRARY(SoQt_LIBRARY NAMES ${SOQT_NAMES})

      IF (SoQt_INCLUDE_DIR AND SoQt_LIBRARY)
	SET(SoQt_FOUND TRUE)
      ENDIF (SoQt_INCLUDE_DIR AND SoQt_LIBRARY)
    ENDIF(NOT SoQt_FOUND)


    # Process stuff
    IF (SoQt_FOUND)
      MESSAGE(STATUS "Found SoQt" "${SoQt_LIBRARY}")
    ELSE (SoQt_FOUND)
      IF (SoQt_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find SoQt. Try setting the COINDIR environment variable to the root of the Coin 3 installation directory.")
      ENDIF (SoQt_FIND_REQUIRED)
    ENDIF (SoQt_FOUND)
  ENDIF(COINDIR)

  # SoQt_DEFINES - only on WIN32
  IF (SoQt_FOUND AND WIN32)
    FIND_FILE(SoQt_pc NAMES SoQt.pc PATHS ${SoQt_INCLUDE_DIR}/../ PATH_SUFFIXES . lib/pkgconfig/ NO_DEFAULT_PATH)
    MARK_AS_ADVANCED(SoQt_pc)
    IF(EXISTS ${SoQt_pc})
      FILE(READ ${SoQt_pc} SoQtPC)
      IF (${SoQtPC} MATCHES SOQT_DLL)
	MESSAGE(STATUS "Found SoQt.pc with -DSOQT_DLL")
	SET(SoQt_DEFINES -DSOQT_DLL)
      ELSE()
	MESSAGE(STATUS "Found SoQt.pc with -DSOQT_NOT_DLL")
	SET(SoQt_DEFINES -DSOQT_NOT_DLL)
      ENDIF()
    ELSE()
      IF(SOQT_NOT_DLL)
	SET(SoQt_DEFINES -DSOQT_NOT_DLL)
      ELSEIF(NOT SOQT_DLL)
	SET(SoQt_DEFINES -DSOQT_DLL)
	MESSAGE(STATUS "WARNING: Could not find SoQt.pc, using -DSOQT_DLL=1. Override or remove this warning using cmake -DSOQT_NOT_DLL=1 or cmake -DSOQT_DLL=1.")
      ENDIF(SOQT_NOT_DLL)
    ENDIF()
  ENDIF()

ENDIF(USE_SIM_FIND)

