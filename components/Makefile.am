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

cutterviewer_SOURCES = \
	computils.h \
	computils.cpp \
	GLOption.h \
	GLOption.cpp \
	SoGuiCutterViewer.h \
	SoGuiCutterViewer.cpp \
	cutterviewer.cpp

backgroundimg_SOURCES = backgroundimg.cpp

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
	cutterviewer.cpp \
	SoGuiCutterViewer.h \
	SoGuiCutterViewer.cpp

noinst_PROGRAMS = renderarea backgroundimg examinerviewer overlay \
	planeviewer flyviewer snapshotviewer cutterviewer \
	$(SLIDERSETS) $(DIRECTIONALLIGHTEDITOR) $(MATERIALEDITOR) \
	$(MATERIALLIST) $(PRINTDIALOG)

############################################################################

computils.cpp: $(srcdir)/computils.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/computils.cpp )

computils.h: $(srcdir)/computils.h.in
	@( cd $(top_builddir); ./config.status --file=components/computils.h )

renderarea.cpp: $(srcdir)/renderarea.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/renderarea.cpp )

backgroundimg.cpp: $(srcdir)/backgroundimg.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/backgroundimg.cpp )

examinerviewer.cpp: $(srcdir)/examinerviewer.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/examinerviewer.cpp )

planeviewer.cpp: $(srcdir)/planeviewer.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/planeviewer.cpp )

flyviewer.cpp: $(srcdir)/flyviewer.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/flyviewer.cpp )

overlay.cpp: $(srcdir)/overlay.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/overlay.cpp )

lightsliderset.cpp: $(srcdir)/lightsliderset.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/lightsliderset.cpp )

materialsliderset.cpp: $(srcdir)/materialsliderset.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/materialsliderset.cpp )

materialsliderset2.cpp: $(srcdir)/materialsliderset2.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/materialsliderset2.cpp )

transformsliderset.cpp: $(srcdir)/transformsliderset.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/transformsliderset.cpp )

materiallist.cpp: $(srcdir)/materiallist.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/materiallist.cpp )

materiallist2.cpp: $(srcdir)/materiallist2.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/materiallist2.cpp )

grapheditor.cpp: $(srcdir)/grapheditor.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/grapheditor.cpp )

roster.cpp: $(srcdir)/roster.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/roster.cpp )

directionallighteditor.cpp: $(srcdir)/directionallighteditor.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/directionallighteditor.cpp )

materialeditor.cpp: $(srcdir)/materialeditor.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/materialeditor.cpp )

printdialog.cpp: $(srcdir)/printdialog.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/printdialog.cpp )

snapshotviewer.cpp: $(srcdir)/snapshotviewer.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/snapshotviewer.cpp )

SoGuiSnapshotViewer.h: $(srcdir)/SoGuiSnapshotViewer.h.in
	@( cd $(top_builddir); ./config.status --file=components/SoGuiSnapshotViewer.h )

SoGuiSnapshotViewer.cpp: $(srcdir)/SoGuiSnapshotViewer.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/SoGuiSnapshotViewer.cpp )

cutterviewer.cpp: $(srcdir)/cutterviewer.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/cutterviewer.cpp )

SoGuiCutterViewer.h: $(srcdir)/SoGuiCutterViewer.h.in
	@( cd $(top_builddir); ./config.status --file=components/SoGuiCutterViewer.h )

SoGuiCutterViewer.cpp: $(srcdir)/SoGuiCutterViewer.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/SoGuiCutterViewer.cpp )

############################################################################
