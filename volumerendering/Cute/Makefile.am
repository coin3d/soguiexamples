#DEFAULT_INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src

BUILT_SOURCES = \
	moc_SoQtGradientDialogP.icc \
	moc_GradientView.icc \
	moc_SoQtColorTableEditorP.icc \
	moc_CurveView.icc

Sources = \
	Gradient.cpp \
	Gradient.h \
	GradientDialog.cpp \
	SoQtColorTableEditor.h \
	SoQtGradientDialog.h \
	curvep/ColorCurve.cpp \
	curvep/ColorCurve.h \
	curvep/ColorTableEditor.cpp \
	curvep/CurveView.cpp \
	curvep/CurveView.h \
	curvep/SbGuiCubicSpline.cpp \
	curvep/SbGuiCubicSpline.h \
	curvep/SoQtColorTableEditorP.h \
	gradientp/GradientView.cpp \
	gradientp/GradientView.h \
	gradientp/ImageItem.cpp \
	gradientp/ImageItem.h \
	gradientp/SoQtGradientDialogP.h \
	gradientp/TickMark.cpp \
	gradientp/TickMark.h

# **************************************************************************

if BUILD_WITH_MSVC
noinst_LIBRARIES = Cute.lst
else
noinst_LIBRARIES = Cute.a
endif

Cute_a_SOURCES = $(Sources)
Cute_lst_SOURCES = $(Sources)

nodist_Cute_a_SOURCES = $(BUILT_SOURCES)
nodist_Cute_lst_SOURCES = $(BUILT_SOURCES)

# **************************************************************************

Cute.lst: $(Cute_lst_OBJECTS)
	@echo "Linking $@..."; \
	rm -f $@; \
	for i in $(Cute_lst_OBJECTS); do echo $$i >>$@; done

# **************************************************************************
# auto-generated Qt moc files.

moc_SoQtGradientDialogP.icc: $(srcdir)/gradientp/SoQtGradientDialogP.h
	$(MOC) -i -o $@ `$(CYGPATH_W) $<`

moc_SoQtColorTableEditorP.icc: $(srcdir)/curvep/SoQtColorTableEditorP.h
	$(MOC) -i -o $@ `$(CYGPATH_W) $<`

moc_GradientView.icc: $(srcdir)/gradientp/GradientView.h
	$(MOC) -i -o $@ `$(CYGPATH_W) $<`

moc_CurveView.icc: $(srcdir)/curvep/CurveView.h
	$(MOC) -i -o $@ `$(CYGPATH_W) $<`

# **************************************************************************
