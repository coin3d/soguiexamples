if HAVE_QT3SUPPORT
SUBDIRS = Cute .
endif

############################################################################
# Conditional build.

if HAVE_SIMAGE
SIMAGE_DEPENDENTS = # rgbload <- FIXME: disabled, used to depend on 32-bit voxel functionality. 20040505 mortene.
else
SIMAGE_DEPENDENTS = 
endif

HAVE_QT3SUPPORT = false

if HAVE_QT3SUPPORT
QT3SUPPORT_DEPENDENTS = readvol orthoslicer
endif

if HAVE_SMALLCHANGE
if HAVE_QT3SUPPORT
SMALLQT3_DEPENDENTS = voleonexplore
endif
endif


if HAVE_SMALLCHANGE
SMALLCHANGE_DEPENDENTS = opaquechair 
else
SMALLCHANGE_DEPENDENTS = 
endif

############################################################################
# Executables.

noinst_PROGRAMS = \
	changingdataset examine  \
	raypick simple8bit $(SIMAGE_DEPENDENTS) \
	fencediagram \
	$(SMALLCHANGE_DEPENDENTS) ${QT3SUPPORT_DEPENDENTS} ${SMALLQT3_DEPENDENTS}

############################################################################
# Executables using the Qt extensions in the "Cute/" subdir.

if BUILD_WITH_MSVC
CUTEARCHIVE = Cute/Cute.lst
else
CUTEARCHIVE = Cute/libCute.a
endif

if USING_QT_4
AM_CPPFLAGS = -DQT3_SUPPORT
endif

# FIXME: only these three examples actually have dependencies on Qt / SoQt,
# and we should fix so the other examples can be built even when not using
# SoQt. 20041021 mortene.
readvol_LDADD = $(CUTEARCHIVE)
orthoslicer_LDADD = $(CUTEARCHIVE)
voleonexplore_LDADD = $(CUTEARCHIVE)

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

# FIXME: disabled, used to depend on 32-bit voxel functionality, which
# is no longer available in SoVolumeData. 20040505 mortene.
# rgbload_SOURCES = rgbload.cpp

simple8bit_SOURCES = simple8bit.cpp utility.cpp utility.h

opaquechair_SOURCES = chair.cpp OpaqueChair.cpp OpaqueChair.h OpaqueChair-iv.h

voleonexplore_SOURCES = voleonexplore.cpp

fencediagram_SOURCES = fencediagram.cpp

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
	voleonexplore.cpp \
	readvol.cpp \
	changingdataset.cpp \
	fencediagram.cpp \
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


# Create Mac OS X application bundles.
app-bundles: all-am
	@case $(target_os) in darwin* ) \
	  echo "Making Mac OS X application bundles in volumerendering."; \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac

