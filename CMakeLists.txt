cmake_minimum_required(VERSION 3.0)

set(Gui "Qt" CACHE STRING "Target GUI for the examples")
set_property(CACHE Gui PROPERTY STRINGS Qt Xt Win)
message(STATUS "Gui='${Gui}'")

# ############################################################################

if(Gui STREQUAL "Qt")
  set(SOQTEXAMPLES TRUE)
  set(GUI QT)
  set(WIDGET QWidget*)
elseif(Gui STREQUAL "Xt")
  set(GUI XT)
  set(WIDGET Widget)
elseif(Gui STREQUAL "Win")
  set(GUI WIN)
  set(WIDGET HWND)
else()
  message(FATAL_ERROR "Only Qt, Win, and Xt supported: please set Gui to one of these values")
endif()

project(So${Gui}Examples VERSION 1.0.0)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

string(TIMESTAMP SO${GUI}EXAMPLES_BUILD_YEAR "%Y")

# ############################################################################
# these will be removed after upgrading CMake minimum version to 3.9.6
set(PROJECT_DESCRIPTION   "Examples for Coin and its GUI toolkits.")
# ############################################################################

if(POLICY CMP0072)
  # get rid of OpenGL GLVND warning from CMake 3.11
  cmake_policy(SET CMP0072 NEW)
endif()

if(POLICY CMP0075)
  # get rid of CMAKE_REQUIRED_LIBRARIES warning from CMake 3.12
  cmake_policy(SET CMP0075 NEW)
endif()

# ############################################################################
# Prevent in-source builds, as they often cause severe build problems
# ############################################################################

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "${CMAKE_PROJECT_NAME} requires an out of source build. Please create a separate build directory and run 'cmake <path_to_${CMAKE_PROJECT_NAME}> [options]' from there.")
endif()

# ############################################################################
# Include necessary submodules
# ############################################################################

# Add path for Coin specific utility scripts
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake" "${CMAKE_MODULE_PATH}")

include(CheckCXXSourceCompiles)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CMakeDependentOption)
include(GNUInstallDirs)

# ############################################################################
# Provide options to customize the build
# ############################################################################

cmake_dependent_option(SOGUIEXAMPLES_USE_QT5 "Prefer Qt5 over Qt4 if available" ON "SOQTEXAMPLES" OFF)

# ############################################################################
# Find all necessary and optional So${Gui} dependencies
# ############################################################################

find_package(OpenGL REQUIRED)
find_package(Coin REQUIRED)
find_package(So${Gui} REQUIRED)

list(APPEND SOGUIEXAMPLES_LINK_LIBRARIES So${Gui}::So${Gui} Coin::Coin)

find_package(SmallChange)
if(SmallChange_FOUND)
  list(APPEND SOGUIEXAMPLES_LINK_LIBRARIES SmallChange::SmallChange)
endif()

find_package(SIMVoleon QUIET)
if(SIMVoleon_FOUND)
  list(APPEND SOGUIEXAMPLES_LINK_LIBRARIES SIMVoleon::SIMVoleon)
endif()

if(SOQTEXAMPLES)
  if(SOGUIEXAMPLES_USE_QT5)
    find_package(Qt5 COMPONENTS Core Gui OpenGL Widgets UiTools QUIET)
  endif()

  if(Qt5_FOUND)
    set(SOGUIEXAMPLES_QT_TARGETS Qt5::Widgets Qt5::Gui Qt5::Core Qt5::OpenGL Qt5::UiTools)
  else()
    set(QT_USE_IMPORTED_TARGETS ON)
    find_package(Qt4 COMPONENTS QtGui QtCore QtOpenGL QtUiTools REQUIRED)
    set(SOGUIEXAMPLES_QT_TARGETS Qt4::QtGui Qt4::QtCore Qt4::QtOpenGL Qt4::QtUiTools)
    include(${QT_USE_FILE})
  endif()

  list(APPEND SOGUIEXAMPLES_LINK_LIBRARIES ${SOGUIEXAMPLES_QT_TARGETS})
endif()

# ##########################################################################
# Setup build environment
# ##########################################################################

if(MSVC)
  add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE -D_CRT_SECURE_NO_DEPRECATE -D_CRT_SECURE_NO_WARNINGS -D_USE_MATH_DEFINES)
  add_compile_options(/MP)
endif()

# ############################################################################
# Tests for Coin features
# ############################################################################

include(coinFeatureTest)

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
