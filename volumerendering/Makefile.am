############################################################################
# Conditional build.

if HAVE_SIMAGE
SIMAGE_DEPENDENTS = rgbload
else
SIMAGE_DEPENDENTS = 
endif

############################################################################
# Executables.

noinst_PROGRAMS = \
	readvol changingdataset examine orthoslicer \
	raypick simple8bit $(SIMAGE_DEPENDENTS) \
	opaquechair

############################################################################
# Common sources.

TRANSFERFUNCTIONSRC = \
	SoTransferFunction_ctrl.cpp SoTransferFunction_ctrl.h moc_SoTransferFunction_ctrl.cpp \
	TransferFunctionHandler.cpp TransferFunctionHandler.h moc_TransferFunctionHandler.cpp

VOLUMERENDERSRC = \
	SoVolumeRender_ctrl.cpp SoVolumeRender_ctrl.h moc_SoVolumeRender_ctrl.cpp \
	VolumeRenderHandler.cpp VolumeRenderHandler.h moc_VolumeRenderHandler.cpp

ORTHOSLICESRC = \
	SoOrthoSlice_ctrl.cpp SoOrthoSlice_ctrl.h moc_SoOrthoSlice_ctrl.cpp \
	OrthoSliceHandler.cpp OrthoSliceHandler.h moc_OrthoSliceHandler.cpp

############################################################################
# A test reader and viewer of VOL files.

readvol_SOURCES = readvol.cpp $(TRANSFERFUNCTIONSRC) $(VOLUMERENDERSRC)

############################################################################
# For testing orthogonal slicing functionality.

orthoslicer_SOURCES = \
	orthoslicer.cpp utility.cpp utility.h \
	$(TRANSFERFUNCTIONSRC) $(ORTHOSLICESRC)

############################################################################
# misc examples

changingdataset_SOURCES = changingdataset.cpp

examine_SOURCES = examine.cpp utility.cpp utility.h

raypick_SOURCES = raypick.cpp utility.cpp utility.h

rgbload_SOURCES = rgbload.cpp

simple8bit_SOURCES = simple8bit.cpp utility.cpp utility.h

opaquechair_SOURCES = chair.cpp OpaqueChair.cpp OpaqueChair.h OpaqueChair-iv.h

############################################################################

SoTransferFunction_ctrl.h: $(srcdir)/SoTransferFunction_ctrl.ui
	$(UIC) `$(CYGPATH_W) $<` -o $@

SoTransferFunction_ctrl.cpp: $(srcdir)/SoTransferFunction_ctrl.ui SoTransferFunction_ctrl.h
	$(UIC) -impl $*.h `$(CYGPATH_W) $<` -o $@

moc_SoTransferFunction_ctrl.cpp: SoTransferFunction_ctrl.h
	$(MOC) -o $@ `$(CYGPATH_W) $<`

moc_TransferFunctionHandler.cpp: $(srcdir)/TransferFunctionHandler.h
	$(MOC) -o $@ `$(CYGPATH_W) $<`

############################################################################

SoVolumeRender_ctrl.h: $(srcdir)/SoVolumeRender_ctrl.ui
	$(UIC) `$(CYGPATH_W) $<` -o $@

SoVolumeRender_ctrl.cpp: $(srcdir)/SoVolumeRender_ctrl.ui SoVolumeRender_ctrl.h
	$(UIC) -impl $*.h `$(CYGPATH_W) $<` -o $@

moc_SoVolumeRender_ctrl.cpp: SoVolumeRender_ctrl.h
	$(MOC) -o $@ `$(CYGPATH_W) $<`

moc_VolumeRenderHandler.cpp: $(srcdir)/VolumeRenderHandler.h
	$(MOC) -o $@ `$(CYGPATH_W) $<`

############################################################################

SoOrthoSlice_ctrl.h: $(srcdir)/SoOrthoSlice_ctrl.ui
	$(UIC) `$(CYGPATH_W) $<` -o $@

SoOrthoSlice_ctrl.cpp: $(srcdir)/SoOrthoSlice_ctrl.ui SoOrthoSlice_ctrl.h
	$(UIC) -impl $*.h `$(CYGPATH_W) $<` -o $@

moc_SoOrthoSlice_ctrl.cpp: SoOrthoSlice_ctrl.h
	$(MOC) -o $@ `$(CYGPATH_W) $<`

moc_OrthoSliceHandler.cpp: $(srcdir)/OrthoSliceHandler.h
	$(MOC) -o $@ `$(CYGPATH_W) $<`

############################################################################

BUILT_SOURCES = \
	readvol.cpp \
	changingdataset.cpp \
	\
	SoTransferFunction_ctrl.cpp SoTransferFunction_ctrl.h moc_SoTransferFunction_ctrl.cpp \
	moc_TransferFunctionHandler.cpp \
	\
	SoVolumeRender_ctrl.cpp SoVolumeRender_ctrl.h moc_SoVolumeRender_ctrl.cpp \
	moc_VolumeRenderHandler.cpp \
	\
	SoOrthoSlice_ctrl.cpp SoOrthoSlice_ctrl.h moc_SoOrthoSlice_ctrl.cpp \
	moc_OrthoSliceHandler.cpp

############################################################################
