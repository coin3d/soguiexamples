cmake_minimum_required(VERSION 3.0)

set(Gui Qt)
set(GUI QT)
set(WIDGET QWidget*)

project(So${Gui}Examples VERSION 1.0.0)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

# ############################################################################
# these will be removed after upgrading CMake minimum version to 3.9.6
set(PROJECT_DESCRIPTION   "Examples for Coin and its GUI toolkits.")
# ############################################################################
 
string(TIMESTAMP SO${GUI}EXAMPLES_BUILD_YEAR "%Y")

if(POLICY CMP0072)
  # get rid of OpenGL GLVND warning from CMake 3.11
  cmake_policy(SET CMP0072 NEW)
endif()

if(POLICY CMP0075)
  # get rid of CMAKE_REQUIRED_LIBRARIES warning from CMake 3.12
  cmake_policy(SET CMP0075 NEW)
endif()

# ############################################################################
# Macros
# ############################################################################

# This is a convenience macro for generating better tree structures in VS solutions.
# Running this in any directory will affect all libraries/executables at that location.
macro(SIM_VS_GENERATE_BASIC_TREE)
  source_group("Source" REGULAR_EXPRESSION \\.cpp)
  source_group("Headers" REGULAR_EXPRESSION \\.h)

  source_group("Source\\Generated Moc files" REGULAR_EXPRESSION moc_*)
  source_group("Source\\Generated Qrc files" REGULAR_EXPRESSION [^\\.]qrc_*)
  source_group("Resources" REGULAR_EXPRESSION .*\\.qrc)

  source_group("Build" REGULAR_EXPRESSION \\.txt)
  source_group("Build\\Rules" REGULAR_EXPRESSION \\.rule)
endmacro()

function(dump_variable)
  if (HAVE_DEBUG)
    foreach(f ${ARGN})
      message("${f} = ${${f}}")
    endforeach()
  endif(HAVE_DEBUG)
endfunction(dump_variable)

# ############################################################################
# Provide options to customise the build
# ############################################################################

option(HAVE_DEBUG "Add debugging information during the configure process")

set(CURRENT_BUILD_DIR SoGuiExamples)

# ############################################################################
# Find all necessary and optional SoQt dependencies
# ############################################################################

find_package(OpenGL REQUIRED)
find_package(Coin REQUIRED)
find_package(SoQt REQUIRED)
find_package(Qt5 COMPONENTS UiTools REQUIRED)
set(LINK_LIBRARY ${LINK_LIBRARY} ${SoQt_LIBRARY} Qt5::UiTools)

find_package(SmallChange)
if (SmallChange_FOUND)
  add_definitions(${SmallChange_DEFINES})
  set(LINK_LIBRARY ${LINK_LIBRARY} ${SmallChange_LIBRARIES})
endif()

find_package(SIMVoleon QUIET)
IF (SIMVoleon_FOUND)
  add_definitions(${SIMVoleon_DEFINES})
  set(LINK_LIBRARY ${LINK_LIBRARY} ${SIMVoleon_LIBRARY})
endif()

dump_variable(
  Coin_DIR
  Coin_DEFINES
  Coin_LIBRARY
  Coin_INCLUDE_DIR
  QT_INCLUDE_DIR
  SoQt_DIR
  SoQt_DEFINES
  SoQt_LIBRARY
  SmallChange_LIBRARIES
  SIMVoleon_LIBRARY
  LINK_LIBRARY
)

# ##########################################################################
# Setup build environment
# ##########################################################################

link_directories(Qt5::Core ${Coin_LIB_DIR} ${OPENGL_gl_DIRECTORY})
# add_definitions("-DQT_NO_VERSION_TAGGING")

#Add header directories
include_directories(BEFORE
  ${SoQt_INCLUDE_DIRS}
  ${Coin_INCLUDE_DIR}
  ${Qt5Core_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIR}
)

if(MSVC)
  message(STATUS "MSVC Version: " ${MSVC_VERSION})
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
endif()

# INCLUDE(SimQtMacros)

# set(LINK_LIBRARY ${LINK_LIBRARY} SoQt)

# ############################################################################
# Tests for Coin
# ############################################################################

set(COIN_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
set(COIN_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")
include(${COIN_CMAKE_DIR}/Confugure.cmake)

# ############################################################################
# Setup targets in subdirectories
# ############################################################################

add_subdirectory(actions)
add_subdirectory(annex)
add_subdirectory(coin-competitions)
add_subdirectory(components)
add_subdirectory(draggers)
add_subdirectory(engines)
add_subdirectory(eyecandy)
add_subdirectory(manipulators)
add_subdirectory(nodekits)
add_subdirectory(nodes)
add_subdirectory(sensors)
add_subdirectory(sound)
add_subdirectory(volumerendering)
