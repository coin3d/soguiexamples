# ############################################################################
# Conditional defines
# ############################################################################

if(SmallChange_FOUND)
  add_definitions(-DHAVE_SMALLCHANGE_LIBRARY)
endif()
if(SIMVoleon_FOUND)
  add_definitions(-DHAVE_SIMVOLEON_LIBRARY)
endif()

check_include_file(windows.h HAVE_WINDOWS_H)
if(HAVE_WINDOWS_H)
  add_definitions(-DHAVE_WINDOWS_H)
endif()
# Checks specific OpenGL configurations
if(HAVE_WINDOWS_H)
  check_include_files("windows.h;GL/gl.h" HAVE_GL_GL_H)
  if(HAVE_GL_GL_H)
    add_definitions(-DHAVE_GL_GL_H)
  endif()
elseif(APPLE AND NOT COIN_BUILD_MAC_X11)
  check_include_file(OpenGL/gl.h HAVE_OPENGL_GL_H)
  if(HAVE_OPENGL_GL_H)
    add_definitions(-DHAVE_OPENGL_GL_H)
  endif()
else()
  check_include_files("GL/gl.h" HAVE_GL_GL_H)
  if(HAVE_GL_GL_H)
    add_definitions(-DHAVE_GL_GL_H)
  endif()
endif()

set(CMAKE_REQUIRED_LIBRARIES Coin::Coin So${Gui}::So${Gui})

check_cxx_source_compiles("
  #include <Inventor/collision/SoIntersectionDetectionAction.h>
  int main() { SoIntersectionDetectionAction ida; ida.setDraggersEnabled(FALSE); return 0; }
" HAVE_SOINTERSECTIONDETECTIONACTION)
check_cxx_source_compiles("
  #include <Inventor/nodes/SoImage.h>
  int main() { SoImage * p = new SoImage; return 0; }
" HAVE_SOIMAGE)
check_cxx_source_compiles("
  #include <Inventor/annex/HardCopy/SoHardCopy.h>
  int main() { const char * v = SoHardCopy::getVersion(); return 0; }
" HAVE_HARDCOPY)
check_cxx_source_compiles("
  #include <Inventor/actions/SoGLRenderAction.h>
  int main() { int i = SoGLRenderAction::SORTED_OBJECT_SORTED_TRIANGLE_BLEND; return 0; }
" HAVE_SOGLRENDERACTION_SORTED_OBJECT_SORTED_TRIANGLE_BLEND)
check_cxx_source_compiles("
  #include <Inventor/nodes/SoExtSelection.h>
  int main() { SoExtSelection * p = new SoExtSelection; return 0; }
" HAVE_SOEXTSELECTION)
check_cxx_source_compiles("
  #include <Inventor/nodes/SoExtSelection.h>
  int main() { SoExtSelection * p = new SoExtSelection; p->lassoMode = SoExtSelection::VISIBLE_SHAPES; return 0; }
" HAVE_SOEXTSELECTION_LASSOMODE)
check_cxx_source_compiles("
  #include <Inventor/nodes/SoBumpMap.h>
  int main() { SoBumpMap * p = new SoBumpMap; return 0; }
" HAVE_SOBUMPMAP)
check_cxx_source_compiles("
  #include <Inventor/nodes/SoBumpMapTransform.h>
  int main() { SoBumpMapTransform * p = new SoBumpMapTransform; return 0; }
" HAVE_SOBUMPMAPTRANSFORM)
check_cxx_source_compiles("
  #include <Inventor/nodes/SoShaderProgram.h>
  int main() { SoShaderProgram * p = new SoShaderProgram; return 0; }
" HAVE_SOSHADERPROGRAM)
check_cxx_source_compiles("
  #include <Inventor/nodes/SoFragmentShader.h>
  int main() { SoFragmentShader * p = new SoFragmentShader; return 0; }
" HAVE_SOFRAGMENTSHADER)
check_cxx_source_compiles("
  #include <Inventor/nodes/SoVertexShader.h>
  int main() { SoVertexShader * p = new SoVertexShader; return 0; }
" HAVE_SOVERTEXSHADER)
check_cxx_source_compiles("
  #include <Inventor/nodes/SoTextureUnit.h>
  int main() { SoTextureUnit * p = new SoTextureUnit; return 0; }
" HAVE_SOTEXTUREUNIT)
check_cxx_source_compiles("
  #include <Inventor/nodes/SoTextureScalePolicy.h>
  int main() { SoTextureScalePolicy * p = new SoTextureScalePolicy; return 0; }
" HAVE_SOTEXTURESCALEPOLICY)
check_cxx_source_compiles("
  #include <Inventor/nodes/SoSceneTexture2.h>
  int main() { SoSceneTexture2 * p = new SoSceneTexture2; return 0; }
" HAVE_SOSCENETEXTURE2)
check_cxx_source_compiles("
  #include <Inventor/nodes/SoPolygonOffset.h>
  int main() { SoPolygonOffset * p = new SoPolygonOffset; return 0; }
" HAVE_SOPOLYGONOFFSET)
check_cxx_source_compiles("
  #include <Inventor/nodes/SoMarkerSet.h>
  int main() { SoMarkerSet * p = new SoMarkerSet; return 0; }
" HAVE_SOMARKERSET)

check_cxx_source_compiles("
  #include <Inventor/${Gui}/viewers/So${Gui}ExaminerViewer.h>
  int main() { So${Gui}ExaminerViewer * viewer = (So${Gui}ExaminerViewer *) 0; viewer->setFullScreen(FALSE); return 0; }
" HAVE_SOCOMPONENT_SETFULLSCREEN)
check_cxx_source_compiles("
  #include <Inventor/${Gui}/viewers/So${Gui}ExaminerViewer.h>
  int main() { So${Gui}ExaminerViewer * viewer = (So${Gui}ExaminerViewer *) 0; viewer->setStereoViewing(FALSE); return 0; }
" HAVE_VIEWER_STEREO_VIEWING)
check_cxx_source_compiles("
  #include <Inventor/${Gui}/viewers/So${Gui}ExaminerViewer.h>
  int main() { So${Gui}ExaminerViewer * viewer = (So${Gui}ExaminerViewer *) 0; viewer->setQuadBufferStereo(0); return 0; }
" HAVE_VIEWER_QUADBUFFER_STEREO)
check_cxx_source_compiles("
  #include <Inventor/${Gui}/So${Gui}RenderArea.h>
  int main() { So${Gui}RenderArea * viewer = (So${Gui}RenderArea *) 0; viewer->setAccumulationBuffer(FALSE); return 0; }
" HAVE_SOGUIGLWIDGET_ACCUMULATIONBUFFER)

unset(CMAKE_REQUIRED_LIBRARIES)

if(HAVE_SOPOLYGONOFFSET)
  add_definitions(-DHAVE_SOPOLYGONOFFSET)
endif()

if(HAVE_SOMARKERSET)
  add_definitions(-DHAVE_SOMARKERSET)
endif()

if(HAVE_SOIMAGE)
  add_definitions(-DHAVE_SOIMAGE)
endif()

if(HAVE_SOTEXTURESCALEPOLICY)
  add_definitions(-DHAVE_SOTEXTURESCALEPOLICY)
endif()

if(HAVE_SOTEXTUREUNIT)
  add_definitions(-DHAVE_SOTEXTUREUNIT)
endif()

if(HAVE_SOBUMPMAP)
  add_definitions(-DHAVE_SOBUMPMAP)
endif()

if(HAVE_SOBUMPMAPTRANSFORM)
  add_definitions(-DHAVE_SOBUMPMAPTRANSFORM)
endif()

if(HAVE_SOSCENETEXTURE2)
  add_definitions(-DHAVE_SOSCENETEXTURE2)
endif()

if(HAVE_SOEXTSELECTION)
  add_definitions(-DHAVE_SOEXTSELECTION)
endif()

if(HAVE_SOEXTSELECTION_LASSOMODE)
  add_definitions(-DHAVE_SOEXTSELECTION_LASSOMODE)
endif()

if(HAVE_SOSHADERPROGRAM)
  add_definitions(-DHAVE_SOSHADERPROGRAM)
endif()

if(HAVE_SOFRAGMENTSHADER)
  add_definitions(-DHAVE_SOFRAGMENTSHADER)
endif()

if(HAVE_SOVERTEXSHADER)
  add_definitions(-DHAVE_SOVERTEXSHADER)
endif()

if(HAVE_SOGLRENDERACTION_SORTED_OBJECT_SORTED_TRIANGLE_BLEND)
  add_definitions(-DHAVE_SOGLRENDERACTION_SORTED_OBJECT_SORTED_TRIANGLE_BLEND)
endif()

if(HAVE_SOCOMPONENT_SETFULLSCREEN)
  add_definitions(-DHAVE_SOCOMPONENT_SETFULLSCREEN)
endif()

if(HAVE_VIEWER_STEREO_VIEWING)
  add_definitions(-DHAVE_VIEWER_STEREO_VIEWING)
endif()

if(HAVE_VIEWER_QUADBUFFER_STEREO)
  add_definitions(-DHAVE_VIEWER_QUADBUFFER_STEREO)
endif()

if(HAVE_SOGUIGLWIDGET_ACCUMULATIONBUFFER)
  add_definitions(-DHAVE_SOGUIGLWIDGET_ACCUMULATIONBUFFER)
endif()

if(HAVE_SOINTERSECTIONDETECTIONACTION)
  add_definitions(-DHAVE_SOINTERSECTIONDETECTIONACTION)
endif()

if(HAVE_HARDCOPY)
  add_definitions(-DHAVE_HARDCOPY)
endif()
