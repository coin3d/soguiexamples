set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}/curvep
  ${CMAKE_CURRENT_BINARY_DIR}/gradientp
)

set(cute_SRC
  Gradient.cpp
  Gradient.h
  GradientDialog.cpp
  SoQtColorTableEditor.h
  SoQtGradientDialog.h
  curvep/ColorCurve.cpp
  curvep/ColorCurve.h
  curvep/ColorTableEditor.cpp
  curvep/CurveView.cpp
  curvep/CurveView.h
  curvep/SbGuiCubicSpline.cpp
  curvep/SbGuiCubicSpline.h
  curvep/SoQtColorTableEditorP.h
  gradientp/GradientView.cpp
  gradientp/GradientView.h
  gradientp/ImageItem.cpp
  gradientp/ImageItem.h
  gradientp/SoQtGradientDialogP.h
  gradientp/TickMark.cpp
  gradientp/TickMark.h
)

add_library(CUTE STATIC ${cute_SRC} ${cute_HEADERS})
target_link_libraries(CUTE PUBLIC ${SOGUIEXAMPLES_LINK_LIBRARIES})
