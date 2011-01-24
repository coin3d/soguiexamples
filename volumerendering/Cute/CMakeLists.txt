INCLUDE_DIRECTORIES(./)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/curvep)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/gradientp)
SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/volumerendering/Cute)
INCLUDE_DIRECTORIES(${CONF_FILE_DIR})

SET(cute_HEADERS gradientp/SoQtGradientDialogP.h curvep/SoQtColorTableEditorP.h gradientp/GradientView.h curvep/CurveView.h)

QT4_WRAP_CPP(cute_HEADERS_MOC ${cute_HEADERS})

SET(cute_SRC 
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

#Generate the tree structure in the VS Projects.
SIM_VS_GENERATE_BASIC_TREE()

ADD_LIBRARY(CUTE STATIC ${cute_SRC} ${cute_HEADERS_MOC})