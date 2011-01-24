CMAKE_MINIMUM_REQUIRED(VERSION 2.6) # Or does this work on 2.4? 2008-05-15, oyshole
SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true) # Avoid unneccesary code

PROJECT(SoGuiExamples)
SET(CURRENT_BUILD_DIR SoGuiExamples)
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/SIMCMakeMacros/")

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


#Add libs
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(Coin REQUIRED) # FIXME: The results of this macro is not cached.
SET(QT_USE_QTDESIGNER true)
SET(QT_USE_QTTEST true)
SET(QT_USE_QTOPENGL true)
SET(QT_USE_QTUITOOLS true)
ADD_DEFINITIONS(-DQT3_SUPPORT)
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})

FIND_PACKAGE(SmallChange REQUIRED)
FIND_PACKAGE(SoQt REQUIRED)
FIND_PACKAGE(SIMVoleon REQUIRED)

LINK_DIRECTORIES(${QT_LIB_DIR} ${Coin_LIB_DIR} ${OPENGL_gl_DIRECTORY})

#Add header directories
INCLUDE_DIRECTORIES(${Coin_INCLUDE_DIR} ${QT_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

#Add definitions really need?
ADD_DEFINITIONS(${Coin_DEFINES})
ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(${SmallChange_DEFINES})
ADD_DEFINITIONS(${SoQt_DEFINES})
ADD_DEFINITIONS(${SIMVoleon_DEFINES})

IF(MSVC)
  MESSAGE(STATUS "MSVC Version: " ${MSVC_VERSION})
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
ENDIF()

INCLUDE(SimQtMacros)

SET(LINK_LIBRARY ${Coin_LIBRARY} ${SmallChange_LIBRARY} ${SoQt_LIBRARY})

#To configure files
SET(Gui "Qt")
SET(GUI "QT")
SET(WIDGET "QWidget* ")

# Tests for coin
SET(COIN_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
SET(COIN_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")
INCLUDE(${COIN_CMAKE_DIR}/coinTest.cmake)

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