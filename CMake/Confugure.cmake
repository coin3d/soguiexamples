# ############################################################################
# Macros
# ############################################################################

macro(define_if GUARD MSG)
  if (${${GUARD}})
    string (REPLACE ";" " -D" DEFS "${ARGN}")
    add_definitions(-D${DEFS})
    message(STATUS "have ${MSG}")
  else()
    message(STATUS "do not have ${MSG}")
  endif()
endmacro()

macro(define_if_compile srcfile DEFINE)
  if ("${ARGV2}" STREQUAL "QT")
    try_compile(TEST_RESULT
      ${COIN_BUILD_DIR}
      ${COIN_CMAKE_DIR}/${srcfile}
      CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}" "-DLINK_LIBRARIES:STRING=SoQt"
                  "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}" "-DINCLUDE_DIRECTORIES:STRING=${QT_INCLUDE_DIR}"
      COMPILE_DEFINITIONS ${Coin_DEFINES} ${SoQt_DEFINES}
      OUTPUT_VARIABLE OUTPUT)
  else()
    try_compile(TEST_RESULT
      ${COIN_BUILD_DIR}
      ${COIN_CMAKE_DIR}/${srcfile}
      CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
                  "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)
  endif()
  string(REPLACE "HAVE_" "" name "${DEFINE}")
  string(TOLOWER ${name} name)
  define_if(TEST_RESULT ${name} ${DEFINE})
endmacro(define_if_compile)

# ############################################################################
# Conditional defines
# ############################################################################

define_if(SmallChange_FOUND   "small_change" HAVE_SMALLCHANGE_LIBRARY)
define_if(SIMVoleon_FOUND     "voleon"       HAVE_SIMVOLEON_LIBRARY)
define_if(QT_QT3SUPPORT_FOUND "qt3"          HAVE_QT3SUPPORT_LIBRARY)

if(OPENGL_FOUND)
  if (WIN32)
    if (CYGWIN)
      if(OPENGL_INCLUDE_DIR)
        add_definitions(-DHAVE_GL_GL_H)
      endif(OPENGL_INCLUDE_DIR)
    else (CYGWIN)
      #test windows.h
      try_compile(WINDOWS_header 
        ${COIN_BUILD_DIR}
        ${COIN_CMAKE_DIR}/windowTest.cxx
        OUTPUT_VARIABLE OUTPUT)
      if(WINDOWS_header)
        add_definitions(-DHAVE_WINDOWS_H)
        message(STATUS "have WINDOWS")
        #test GL/gl.h
        try_compile(GL_header 
          ${COIN_BUILD_DIR}
          ${COIN_CMAKE_DIR}/glGL.cxx 
          CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${OPENGL_LIBRARY}"
          OUTPUT_VARIABLE OUTPUT)
        if(GL_header)
          add_definitions(-DHAVE_GL_GL_H)
          message(STATUS "have GL dir")
        else(GL_header)
          message(STATUS "do not have GL dir")
        endif(GL_header)
        #test OpenGL/gl.h
        try_compile(OpenGL_header 
          ${COIN_BUILD_DIR}
          ${COIN_CMAKE_DIR}/openglGL.cxx 
          CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${OPENGL_LIBRARY}"
          OUTPUT_VARIABLE OUTPUT)
        if(OpenGL_header)
          add_definitions(-DHAVE_OPENGL_GL_H)
          message(STATUS "have OpenGL dir")
        else(OpenGL_header)
          message(STATUS "do not have OpenGL dir")
        endif(OpenGL_header)
      else(WINDOWS_header)
        message(STATUS "do not have windows.h")
      endif(WINDOWS_header)
    endif (CYGWIN)
  else (WIN32)
    if (APPLE)
      if(OPENGL_INCLUDE_DIR)
        add_definitions(-DHAVE_OPENGL_GL_H)
      endif(OPENGL_INCLUDE_DIR)
    else(APPLE)
      if(OPENGL_INCLUDE_DIR)
        add_definitions(-DHAVE_GL_GL_H)
      endif(OPENGL_INCLUDE_DIR)
    endif(APPLE)
  endif (WIN32)
endif(OPENGL_FOUND)

# ############################################################################
# configure files
# ############################################################################

configure_file(${COIN_CMAKE_DIR}/coinTestExaminerViewer_setfullscreen.cxx.in ${COIN_CMAKE_DIR}/coinTestExaminerViewer_setfullscreen.cxx)
configure_file(${COIN_CMAKE_DIR}/coinTestExaminerViewer_viewer_stereo_viewing.cxx.in ${COIN_CMAKE_DIR}/coinTestExaminerViewer_viewer_stereo_viewing.cxx)
configure_file(${COIN_CMAKE_DIR}/coinTestExaminerViewer_viewer_quadbuffer_stereo.cxx.in ${COIN_CMAKE_DIR}/coinTestExaminerViewer_viewer_quadbuffer_stereo.cxx)
configure_file(${COIN_CMAKE_DIR}/coinTestExaminerRenderArea.cxx.in ${COIN_CMAKE_DIR}/coinTestExaminerRenderArea.cxx)

# ############################################################################
# test .cxx files
# ############################################################################

#test sopolygonoffset
define_if_compile(coinTestSoPolygonOffset.cxx HAVE_SOPOLYGONOFFSET)
#test somarkerset
define_if_compile(coinTestSoMarkerSet.cxx HAVE_SOMARKERSET)
#test soimage
define_if_compile(coinTestSoImage.cxx HAVE_SOIMAGE)
#test sotexturescalepolicy
define_if_compile(coinTestSoTextureScalePolicy.cxx HAVE_SOTEXTURESCALEPOLICY)
#test sotextureunit
define_if_compile(coinTestSoTextureUnit.cxx HAVE_SOTEXTUREUNIT)
#test sobumpmap
define_if_compile(coinTestSoBumpMap.cxx HAVE_SOBUMPMAP)
#test sobumpmaptransform
define_if_compile(coinTestSoBumpMapTransform.cxx HAVE_SOBUMPMAPTRANSFORM)
#test soscenetexture2
define_if_compile(coinTestSoSceneTexture2.cxx HAVE_SOSCENETEXTURE2)
#test soextselection
define_if_compile(coinTestSoExtSelection.cxx HAVE_SOEXTSELECTION)
#test soextselection_lassomode
define_if_compile(coinTestSoExtSelection_lassomode.cxx HAVE_SOEXTSELECTION_LASSOMODE)
#test soshaderprogram
define_if_compile(coinTestSoShaderProgram.cxx HAVE_SOSHADERPROGRAM)
#test sofragmentshader
define_if_compile(coinTestSoFragmentShader.cxx HAVE_SOFRAGMENTSHADER)
#test sovertexshader
define_if_compile(coinTestSoVertexShader.cxx HAVE_SOVERTEXSHADER)
#test soglrenderaction
define_if_compile(coinTestSoGLRenderAction.cxx HAVE_SOGLRENDERACTION_SORTED_OBJECT_SORTED_TRIANGLE_BLEND)
#test socomponent_setfullscreen
define_if_compile(coinTestExaminerViewer_setfullscreen.cxx HAVE_SOCOMPONENT_SETFULLSCREEN QT)
#test viewer_stereo_viewing
define_if_compile(coinTestExaminerViewer_viewer_stereo_viewing.cxx HAVE_VIEWER_STEREO_VIEWING QT)
#test viewer_quadbuffer_stereo
define_if_compile(coinTestExaminerViewer_viewer_quadbuffer_stereo.cxx HAVE_VIEWER_QUADBUFFER_STEREO QT)
#test soguiglwidget_accumulationbuffer
define_if_compile(coinTestExaminerRenderArea.cxx HAVE_SOGUIGLWIDGET_ACCUMULATIONBUFFER QT)
#test sointersectiondetectionaction
define_if_compile(coinTestSoIntersectionDetectionAction.cxx HAVE_SOINTERSECTIONDETECTIONACTION)
#test hardcopy
define_if_compile(coinTestSoHardCopy.cxx HAVE_HARDCOPY)
