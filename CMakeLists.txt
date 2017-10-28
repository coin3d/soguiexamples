CMAKE_MINIMUM_REQUIRED(VERSION 2.6) # Or does this work on 2.4? 2008-05-15, oyshole
SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true) # Avoid unneccesary code

PROJECT(SoGuiExamples)
SET(CURRENT_BUILD_DIR SoGuiExamples)
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/SIMCMakeMacros/")

option(HAVE_DEBUG "Add debugging information during the configure process")

# This is a convenience macro for generating better tree structures in VS solutions.
# Running this in any directory will affect all libraries/executables at that location.
MACRO(SIM_VS_GENERATE_BASIC_TREE)
  SOURCE_GROUP("Source" REGULAR_EXPRESSION \\.cpp)
  SOURCE_GROUP("Headers" REGULAR_EXPRESSION \\.h)

  SOURCE_GROUP("Source\\Generated Moc files" REGULAR_EXPRESSION moc_*)
  SOURCE_GROUP("Source\\Generated Qrc files" REGULAR_EXPRESSION [^\\.]qrc_*)
  SOURCE_GROUP("Resources" REGULAR_EXPRESSION .*\\.qrc)

  SOURCE_GROUP("Build" REGULAR_EXPRESSION \\.txt)
  SOURCE_GROUP("Build\\Rules" REGULAR_EXPRESSION \\.rule)
ENDMACRO()

function(dump_variable)
  if (HAVE_DEBUG)
    foreach(f ${ARGN})
      message("${f} = ${${f}}")
    endforeach()
  endif(HAVE_DEBUG)
endfunction(dump_variable)

#Add libs
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(Coin REQUIRED CONFIG) # FIXME: The results of this macro is not cached.
find_package(SoQt REQUIRED CONFIG)
SET(QT_USE_QTDESIGNER true)
SET(QT_USE_QTTEST true)
SET(QT_USE_QTOPENGL true)
SET(QT_USE_QTUITOOLS true)
FIND_PACKAGE(Qt5 REQUIRED Core Widgets)
dump_variable(
Coin_DIR
Coin_DEFINES
SoQt_DIR
SoQt_DEFINES
)
FIND_PACKAGE(SmallChange)
if (SmallChange_FOUND)
  ADD_DEFINITIONS(${SmallChange_DEFINES})
  set(LINK_LIBRARY ${LINK_LIBRARY} ${SmallChange_LIBRARY})
endif(SmallChange_FOUND)
FIND_PACKAGE(SIMVoleon)
IF (SIMVoleon_FOUND)
  ADD_DEFINITIONS(${SIMVoleon_DEFINES})
  set(LINK_LIBRARY ${LINK_LIBRARY} ${SIMVoleon_LIBRARY})
ENDIF (SIMVoleon_FOUND)

LINK_DIRECTORIES(Qt5::Core ${Coin_LIB_DIR} ${OPENGL_gl_DIRECTORY})
add_definitions("-DQT_NO_VERSION_TAGGING")

#Add header directories
include_directories(BEFORE
${SoQt_INCLUDE_DIRS}
${Qt5Core_INCLUDE_DIRS}
${Coin_INCLUDE_DIR}
${OPENGL_INCLUDE_DIR}
)

#Add definitions really need?
ADD_DEFINITIONS(${Coin_DEFINES})
ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(${SoQt_DEFINES})

IF(MSVC)
  MESSAGE(STATUS "MSVC Version: " ${MSVC_VERSION})
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
ENDIF()

INCLUDE(SimQtMacros)

SET(LINK_LIBRARY ${LINK_LIBRARY} Coin::Coin SoQt)

#To configure files
SET(Gui "Qt")
SET(GUI "QT")
SET(WIDGET "QWidget* ")

# Tests for coin
SET(COIN_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
SET(COIN_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")
INCLUDE(${COIN_CMAKE_DIR}/Confugure.cmake)
dump_variable(COIN_CMAKE_DIR)

# Executables fail to build with Qt 5 in the default configuration^M
# without -fPIE. We add that here.^M
set(CMAKE_CXX_FLAGS "-fPIC")

# What to build
ADD_SUBDIRECTORY(actions)
ADD_SUBDIRECTORY(annex)
ADD_SUBDIRECTORY(coin-competitions)
ADD_SUBDIRECTORY(components)
ADD_SUBDIRECTORY(draggers)
ADD_SUBDIRECTORY(engines)
ADD_SUBDIRECTORY(eyecandy)
ADD_SUBDIRECTORY(manipulators)
ADD_SUBDIRECTORY(nodekits)
ADD_SUBDIRECTORY(nodes)
ADD_SUBDIRECTORY(sensors)
ADD_SUBDIRECTORY(sound)
ADD_SUBDIRECTORY(volumerendering)
