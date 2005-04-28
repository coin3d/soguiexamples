############################################################################

## So@Gui@Roster component
#if HAVE_ROSTER
#ROSTER = roster
#else
ROSTER =
#endif

renderarea_SOURCES = \
	computils.h \
	computils.cpp \
	renderarea.cpp

simpleexviewer_SOURCES = \
	simpleexviewer.cpp

examinerviewer_SOURCES = \
	computils.h \
	computils.cpp \
	examinerviewer.cpp

overlay_SOURCES = overlay.cpp

planeviewer_SOURCES = \
	computils.h \
	computils.cpp \
	planeviewer.cpp

flyviewer_SOURCES = \
	computils.h \
	computils.cpp \
	flyviewer.cpp

snapshotviewer_SOURCES = \
	computils.h \
	computils.cpp \
	SoGuiSnapshotViewer.h \
	SoGuiSnapshotViewer.cpp \
	snapshotviewer.cpp

# cutterviewer_SOURCES = \
# 	computils.h \
# 	computils.cpp \
# 	GLOption.h \
# 	GLOption.cpp \
# 	SoGuiCutterViewer.h \
# 	SoGuiCutterViewer.cpp \
# 	cutterviewer.cpp

backgroundimg_SOURCES = backgroundimg.cpp

spaceballdemo_SOURCES = spaceballdemo.cpp

multifileviewer_SOURCES = multifileviewer.cpp

## So@Gui@LightSliderSet component
if HAVE_SLIDERSETS
SLIDERSETS = lightsliderset materialsliderset materialsliderset2 transformsliderset
else
SLIDERSETS =
endif

lightsliderset_SOURCES = \
	lightsliderset.cpp
materialsliderset_SOURCES = \
	materialsliderset.cpp
materialsliderset2_SOURCES = \
	materialsliderset2.cpp
transformsliderset_SOURCES = \
	transformsliderset.cpp

## So@Gui@DirectionalLightEditor component
if HAVE_DIRECTIONALLIGHTEDITOR
DIRECTIONALLIGHTEDITOR = directionallighteditor
else
DIRECTIONALLIGHTEDITOR =
endif

directionallighteditor_SOURCES = \
	directionallighteditor.cpp

## So@Gui@MaterialEditor component
if HAVE_MATERIALEDITOR
MATERIALEDITOR = materialeditor
else
MATERIALEDITOR =
endif

materialeditor_SOURCES = \
	materialeditor.cpp

## So@Gui@MaterialList component
if HAVE_MATERIALLIST
MATERIALLIST = materiallist materiallist2
else
MATERIALLIST =
endif

materiallist_SOURCES = materiallist.cpp
materiallist2_SOURCES = materiallist2.cpp

## So@Gui@PrintDialog component
if HAVE_PRINTDIALOG
PRINTDIALOG = printdialog
else
PRINTDIALOG =
endif

printdialog_SOURCES = \
	printdialog.cpp

############################################################################

BUILT_SOURCES = \
	computils.h \
	computils.cpp \
	roster.cpp \
	renderarea.cpp \
	simpleexviewer.cpp \
	backgroundimg.cpp \
	examinerviewer.cpp \
	planeviewer.cpp \
	flyviewer.cpp \
	lightsliderset.cpp \
	materialsliderset.cpp \
	materialsliderset2.cpp \
	transformsliderset.cpp \
	materiallist.cpp \
	materiallist2.cpp \
	grapheditor.cpp \
	snapshotviewer.cpp \
	SoGuiSnapshotViewer.h \
	SoGuiSnapshotViewer.cpp \
	multifileviewer.cpp \
	spaceballdemo.cpp 
# 	cutterviewer.cpp \
# 	SoGuiCutterViewer.h \
# 	SoGuiCutterViewer.cpp

noinst_PROGRAMS = renderarea simpleexviewer backgroundimg examinerviewer \
	overlay planeviewer flyviewer snapshotviewer spaceballdemo \
	multifileviewer \
	$(SLIDERSETS) $(DIRECTIONALLIGHTEDITOR) $(MATERIALEDITOR) \
	$(MATERIALLIST) $(PRINTDIALOG)

############################################################################

# Create Mac OS X application bundles.
install-exec-local: 
	@case $(target_os) in darwin* ) \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac


