############################################################################
# Executables.

noinst_PROGRAMS = readvol

############################################################################
# A test reader and viewer of VOL files.

readvol_SOURCES = readvol.cpp \
	SoTransferFunction_ctrl.cpp SoTransferFunction_ctrl.h moc_SoTransferFunction_ctrl.cpp \
	TransferFunctionHandler.cpp TransferFunctionHandler.h moc_TransferFunctionHandler.cpp \
	SoVolumeRender_ctrl.cpp SoVolumeRender_ctrl.h moc_SoVolumeRender_ctrl.cpp \
	VolumeRenderHandler.cpp VolumeRenderHandler.h moc_VolumeRenderHandler.cpp

############################################################################

SoTransferFunction_ctrl.h: $(srcdir)/SoTransferFunction_ctrl.ui
	uic `$(CYGPATH_W) $<` -o $@

SoTransferFunction_ctrl.cpp: $(srcdir)/SoTransferFunction_ctrl.ui SoTransferFunction_ctrl.h
	uic -impl $*.h `$(CYGPATH_W) $<` -o $@

moc_SoTransferFunction_ctrl.cpp: SoTransferFunction_ctrl.h
	moc -o $@ `$(CYGPATH_W) $<`

moc_TransferFunctionHandler.cpp: $(srcdir)/TransferFunctionHandler.h
	moc -o $@ `$(CYGPATH_W) $<`

############################################################################

SoVolumeRender_ctrl.h: $(srcdir)/SoVolumeRender_ctrl.ui
	uic `$(CYGPATH_W) $<` -o $@

SoVolumeRender_ctrl.cpp: $(srcdir)/SoVolumeRender_ctrl.ui SoVolumeRender_ctrl.h
	uic -impl $*.h `$(CYGPATH_W) $<` -o $@

moc_SoVolumeRender_ctrl.cpp: SoVolumeRender_ctrl.h
	moc -o $@ $<

moc_VolumeRenderHandler.cpp: $(srcdir)/VolumeRenderHandler.h
	moc -o $@ `$(CYGPATH_W) $<`

############################################################################

BUILT_SOURCES = \
	readvol.cpp \
	SoTransferFunction_ctrl.cpp SoTransferFunction_ctrl.h moc_SoTransferFunction_ctrl.cpp \
	moc_TransferFunctionHandler.cpp

############################################################################
