IF(SmallChange_FOUND)
  ADD_DEFINITIONS(-DHAVE_SMALLCHANGE_LIBRARY)
  MESSAGE(STATUS "have small_change")
ENDIF(SmallChange_FOUND)

IF(SIMVoleon_FOUND)
  ADD_DEFINITIONS(-DHAVE_SIMVOLEON_LIBRARY)
  MESSAGE(STATUS "have voleon")
ENDIF(SIMVoleon_FOUND)

IF(QT_QT3SUPPORT_FOUND)
  ADD_DEFINITIONS(-DHAVE_QT3SUPPORT_LIBRARY)
  MESSAGE(STATUS "have qt3")
ENDIF(QT_QT3SUPPORT_FOUND)

IF(OPENGL_FOUND)
IF (WIN32)

  IF (CYGWIN)
    IF(OPENGL_INCLUDE_DIR)
      ADD_DEFINITIONS(-DHAVE_GL_GL_H)
    ENDIF(OPENGL_INCLUDE_DIR)
  ELSE (CYGWIN)

    #test windows.h
    TRY_COMPILE(WINDOWS_header 
          ${COIN_BUILD_DIR}
        ${COIN_CMAKE_DIR}/windowTest.cxx
	          OUTPUT_VARIABLE OUTPUT)
    IF(WINDOWS_header)

      ADD_DEFINITIONS(-DHAVE_WINDOWS_H)
      MESSAGE(STATUS "have WINDOWS")
	#test GL/gl.h
	TRY_COMPILE(GL_header 
  	    ${COIN_BUILD_DIR}
  	  ${COIN_CMAKE_DIR}/glGL.cxx 
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${OPENGL_LIBRARY}"
     	 	      OUTPUT_VARIABLE OUTPUT)
	IF(GL_header)
	  ADD_DEFINITIONS(-DHAVE_GL_GL_H)
	  MESSAGE(STATUS "have GL dir")
	ELSE(GL_header)
	  MESSAGE(STATUS "do not have GL dir")
	ENDIF(GL_header)

	#test OpenGL/gl.h
	TRY_COMPILE(OpenGL_header 
	      ${COIN_BUILD_DIR}
	    ${COIN_CMAKE_DIR}/openglGL.cxx 
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${OPENGL_LIBRARY}"
	      	      OUTPUT_VARIABLE OUTPUT)
	IF(OpenGL_header)
	  ADD_DEFINITIONS(-DHAVE_OPENGL_GL_H)
	  MESSAGE(STATUS "have OpenGL dir")
	ELSE(OpenGL_header)
	  MESSAGE(STATUS "do not have OpenGL dir")
	ENDIF(OpenGL_header)

    ELSE(WINDOWS_header)
 	 MESSAGE(STATUS "do not have windows.h")
    ENDIF(WINDOWS_header)
  ENDIF (CYGWIN)

ELSE (WIN32)

  IF (APPLE)
    IF(OPENGL_INCLUDE_DIR)
      ADD_DEFINITIONS(-DHAVE_OPENGL_GL_H)
    ENDIF(OPENGL_INCLUDE_DIR)
  ELSE(APPLE)
    IF(OPENGL_INCLUDE_DIR)
      ADD_DEFINITIONS(-DHAVE_GL_GL_H)
    ENDIF(OPENGL_INCLUDE_DIR)
  ENDIF(APPLE)

ENDIF (WIN32)
ENDIF(OPENGL_FOUND)




###configure files
CONFIGURE_FILE(${COIN_CMAKE_DIR}/coinTestExaminerViewer_setfullscreen.cxx.in ${COIN_CMAKE_DIR}/coinTestExaminerViewer_setfullscreen.cxx)

CONFIGURE_FILE(${COIN_CMAKE_DIR}/coinTestExaminerViewer_viewer_stereo_viewing.cxx.in ${COIN_CMAKE_DIR}/coinTestExaminerViewer_viewer_stereo_viewing.cxx)

CONFIGURE_FILE(${COIN_CMAKE_DIR}/coinTestExaminerViewer_viewer_quadbuffer_stereo.cxx.in ${COIN_CMAKE_DIR}/coinTestExaminerViewer_viewer_quadbuffer_stereo.cxx)

CONFIGURE_FILE(${COIN_CMAKE_DIR}/coinTestExaminerRenderArea.cxx.in ${COIN_CMAKE_DIR}/coinTestExaminerRenderArea.cxx)


###test .cxx files
#test sopolygonoffset
TRY_COMPILE(COIN_TEST_SOPOLYGONOFFSET 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestSoPolygonOffset.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOPOLYGONOFFSET)
  ADD_DEFINITIONS(-DHAVE_SOPOLYGONOFFSET)
  MESSAGE(STATUS "have sopolygonoffset")
ELSE(COIN_TEST_SOPOLYGONOFFSET)
  MESSAGE(STATUS "do not have sopolygonoffset")
ENDIF(COIN_TEST_SOPOLYGONOFFSET)


#test somarkerset
TRY_COMPILE(COIN_TEST_SOMARKERSET 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestSoMarkerSet.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOMARKERSET)
  ADD_DEFINITIONS(-DHAVE_SOMARKERSET)
  MESSAGE(STATUS "have somarkerset")
ELSE(COIN_TEST_SOMARKERSET)
  MESSAGE(STATUS "do not have somarkerset")
ENDIF(COIN_TEST_SOMARKERSET)


#test soimage
TRY_COMPILE(COIN_TEST_SOIMAGE 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestSoImage.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOIMAGE)
  ADD_DEFINITIONS(-DHAVE_SOIMAGE)
  MESSAGE(STATUS "have soimage")
ELSE(COIN_TEST_SOIMAGE)
  MESSAGE(STATUS "do not have soimage")
ENDIF(COIN_TEST_SOIMAGE)


#test sotexturescalepolicy
TRY_COMPILE(COIN_TEST_SOTEXTURESCALEPOLICY 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestSoTextureScalePolicy.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOTEXTURESCALEPOLICY)
  ADD_DEFINITIONS(-DHAVE_SOTEXTURESCALEPOLICY)
  MESSAGE(STATUS "have sotexturescalepolicy")
ELSE(COIN_TEST_SOTEXTURESCALEPOLICY)
  MESSAGE(STATUS "do not have sotexturescalepolicy")
ENDIF(COIN_TEST_SOTEXTURESCALEPOLICY)


#test sotextureunit
TRY_COMPILE(COIN_TEST_SOTEXTUREUNIT 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestSoTextureUnit.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOTEXTUREUNIT)
  ADD_DEFINITIONS(-DHAVE_SOTEXTUREUNIT)
  MESSAGE(STATUS "have sotextureunit")
ELSE(COIN_TEST_SOTEXTUREUNIT)
  MESSAGE(STATUS "do not have sotextureunit")
ENDIF(COIN_TEST_SOTEXTUREUNIT)


#test sobumpmap
TRY_COMPILE(COIN_TEST_SOBUMPMAP 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestSoBumpMap.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOBUMPMAP)
  ADD_DEFINITIONS(-DHAVE_SOBUMPMAP)
  MESSAGE(STATUS "have sobumpmap")
ELSE(COIN_TEST_SOBUMPMAP)
  MESSAGE(STATUS "do not have sobumpmap")
ENDIF(COIN_TEST_SOBUMPMAP)


#test sobumpmaptransform
TRY_COMPILE(COIN_TEST_SOBUMPMAPTRANSFORM 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestSoBumpMapTransform.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOBUMPMAPTRANSFORM)
  ADD_DEFINITIONS(-DHAVE_SOBUMPMAPTRANSFORM)
  MESSAGE(STATUS "have sobumpmaptransform")
ELSE(COIN_TEST_SOBUMPMAPTRANSFORM)
  MESSAGE(STATUS "do not have sobumpmaptransform")
ENDIF(COIN_TEST_SOBUMPMAPTRANSFORM)


#test soscenetexture2
TRY_COMPILE(COIN_TEST_SOSCENETEXTURE2 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestSoSceneTexture2.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOSCENETEXTURE2)
  ADD_DEFINITIONS(-DHAVE_SOSCENETEXTURE2)
  MESSAGE(STATUS "have soscenetexture2")
ELSE(COIN_TEST_SOSCENETEXTURE2)
  MESSAGE(STATUS "do not have soscenetexture2")
ENDIF(COIN_TEST_SOSCENETEXTURE2)


#test soextselection
TRY_COMPILE(COIN_TEST_SOEXTSELECTION 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestSoExtSelection.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOEXTSELECTION)
  ADD_DEFINITIONS(-DHAVE_SOEXTSELECTION)
  MESSAGE(STATUS "have soextselection")
ELSE(COIN_TEST_SOEXTSELECTION)
  MESSAGE(STATUS "do not have soextselection")
ENDIF(COIN_TEST_SOEXTSELECTION)


#test soextselection_lassomode
TRY_COMPILE(COIN_TEST_SOEXTSELECTION_LASSOMODE 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestSoExtSelection_lassomode.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOEXTSELECTION_LASSOMODE)
  ADD_DEFINITIONS(-DHAVE_SOEXTSELECTION_LASSOMODE)
  MESSAGE(STATUS "have soextselection_lassomode")
ELSE(COIN_TEST_SOEXTSELECTION_LASSOMODE)
  MESSAGE(STATUS "do not have soextselection_lassomode")
ENDIF(COIN_TEST_SOEXTSELECTION_LASSOMODE)


#test soshaderprogram
TRY_COMPILE(COIN_TEST_SOSHADERPROGRAM 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestSoShaderProgram.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOSHADERPROGRAM)
  ADD_DEFINITIONS(-DHAVE_SOSHADERPROGRAM)
  MESSAGE(STATUS "have soshaderprogram")
ELSE(COIN_TEST_SOSHADERPROGRAM)
  MESSAGE(STATUS "do not have soshaderprogram")
ENDIF(COIN_TEST_SOSHADERPROGRAM)


#test sofragmentshader
TRY_COMPILE(COIN_TEST_SOFRAGMENTSHADER 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestSoFragmentShader.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOFRAGMENTSHADER)
  ADD_DEFINITIONS(-DHAVE_SOFRAGMENTSHADER)
  MESSAGE(STATUS "have sofragmentshader")
ELSE(COIN_TEST_SOFRAGMENTSHADER)
  MESSAGE(STATUS "do not have sofragmentshader")
ENDIF(COIN_TEST_SOFRAGMENTSHADER)


#test sovertexshader
TRY_COMPILE(COIN_TEST_SOVERTEXSHADER 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestSoVertexShader.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOVERTEXSHADER)
  ADD_DEFINITIONS(-DHAVE_SOVERTEXSHADER)
  MESSAGE(STATUS "have sovertexshader")
ELSE(COIN_TEST_SOVERTEXSHADER)
  MESSAGE(STATUS "do not have sovertexshader")
ENDIF(COIN_TEST_SOVERTEXSHADER)


#test soglrenderaction
TRY_COMPILE(COIN_TEST_SOGLRENDERACTION_SORTED_OBJECT_SORTED_TRIANGLE_BLEND 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestSoGLRenderAction.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOGLRENDERACTION_SORTED_OBJECT_SORTED_TRIANGLE_BLEND)
  ADD_DEFINITIONS(-DHAVE_SOGLRENDERACTION_SORTED_OBJECT_SORTED_TRIANGLE_BLEND)
  MESSAGE(STATUS "have soglrenderaction")
ELSE(COIN_TEST_SOGLRENDERACTION_SORTED_OBJECT_SORTED_TRIANGLE_BLEND)
  MESSAGE(STATUS "do not have soglrenderaction")
ENDIF(COIN_TEST_SOGLRENDERACTION_SORTED_OBJECT_SORTED_TRIANGLE_BLEND)


#test socomponent_setfullscreen
TRY_COMPILE(COIN_TEST_SOCOMPONENT_SETFULLSCREEN 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestExaminerViewer_setfullscreen.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"    "-DLINK_LIBRARIES:STRING=${SoQt_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}" "-DINCLUDE_DIRECTORIES:STRING=${QT_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES} ${SoQt_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOCOMPONENT_SETFULLSCREEN)
  ADD_DEFINITIONS(-DHAVE_SOCOMPONENT_SETFULLSCREEN)
  MESSAGE(STATUS "have socomponent_setfullscreen")
ELSE(COIN_TEST_SOCOMPONENT_SETFULLSCREEN)
  MESSAGE(STATUS "do not have socomponent_setfullscreen")
ENDIF(COIN_TEST_SOCOMPONENT_SETFULLSCREEN)


#test viewer_stereo_viewing
TRY_COMPILE(COIN_TEST_VIEWER_STEREO_VIEWING 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestExaminerViewer_viewer_stereo_viewing.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"    "-DLINK_LIBRARIES:STRING=${SoQt_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}" "-DINCLUDE_DIRECTORIES:STRING=${QT_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES} ${SoQt_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_VIEWER_STEREO_VIEWING)
  ADD_DEFINITIONS(-DHAVE_VIEWER_STEREO_VIEWING)
  MESSAGE(STATUS "have viewer_stereo_viewing")
ELSE(COIN_TEST_VIEWER_STEREO_VIEWING)
  MESSAGE(STATUS "do not have viewer_stereo_viewing")
ENDIF(COIN_TEST_VIEWER_STEREO_VIEWING)


#test viewer_quadbuffer_stereo
TRY_COMPILE(COIN_TEST_VIEWER_QUADBUFFER_STEREO 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestExaminerViewer_viewer_quadbuffer_stereo.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"    "-DLINK_LIBRARIES:STRING=${SoQt_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}" "-DINCLUDE_DIRECTORIES:STRING=${QT_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES} ${SoQt_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_VIEWER_QUADBUFFER_STEREO)
  ADD_DEFINITIONS(-DHAVE_VIEWER_QUADBUFFER_STEREO)
  MESSAGE(STATUS "have viewer_quadbuffer_stereo")
ELSE(COIN_TEST_VIEWER_QUADBUFFER_STEREO)
  MESSAGE(STATUS "do not have viewer_quadbuffer_stereo")
ENDIF(COIN_TEST_VIEWER_QUADBUFFER_STEREO)


#test soguiglwidget_accumulationbuffer
TRY_COMPILE(COIN_TEST_SOGUIGLWIDGET_ACCUMULATIONBUFFER 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestExaminerRenderArea.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"    "-DLINK_LIBRARIES:STRING=${SoQt_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}" "-DINCLUDE_DIRECTORIES:STRING=${QT_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES} ${SoQt_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOGUIGLWIDGET_ACCUMULATIONBUFFER)
  ADD_DEFINITIONS(-DHAVE_SOGUIGLWIDGET_ACCUMULATIONBUFFER)
  MESSAGE(STATUS "have soguiglwidget_accumulationbuffer")
ELSE(COIN_TEST_SOGUIGLWIDGET_ACCUMULATIONBUFFER)
  MESSAGE(STATUS "do not have soguiglwidget_accumulationbuffer")
ENDIF(COIN_TEST_SOGUIGLWIDGET_ACCUMULATIONBUFFER)


#test sointersectiondetectionaction
TRY_COMPILE(COIN_TEST_SOINTERSECTIONDETECTIONACTION 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestSoIntersectionDetectionAction.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_SOINTERSECTIONDETECTIONACTION)
  ADD_DEFINITIONS(-DHAVE_SOINTERSECTIONDETECTIONACTION)
  MESSAGE(STATUS "have sointersectiondetectionaction")
ELSE(COIN_TEST_SOINTERSECTIONDETECTIONACTION)
  MESSAGE(STATUS "do not have sointersectiondetectionaction")
ENDIF(COIN_TEST_SOINTERSECTIONDETECTIONACTION)


#test hardcopy
TRY_COMPILE(COIN_TEST_HARDCOPY 
      ${COIN_BUILD_DIR}
    ${COIN_CMAKE_DIR}/coinTestSoHardCopy.cxx
	CMAKE_FLAGS "-DLINK_LIBRARIES:STRING=${Coin_LIBRARY}"
            "-DINCLUDE_DIRECTORIES:STRING=${Coin_INCLUDE_DIR}"
      COMPILE_DEFINITIONS
      ${Coin_DEFINES}
      OUTPUT_VARIABLE OUTPUT)

IF(COIN_TEST_HARDCOPY)
  ADD_DEFINITIONS(-DHAVE_HARDCOPY)
  MESSAGE(STATUS "have hardcopy")
ELSE(COIN_TEST_HARDCOPY)
  MESSAGE(STATUS "do not have hardcopy")
ENDIF(COIN_TEST_HARDCOPY)
