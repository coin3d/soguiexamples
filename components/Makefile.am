############################################################################

## So@Gui@Roster component
#if HAVE_ROSTER
#ROSTER = roster
#else
ROSTER =
#endif

renderarea_SOURCES = \
	renderarea.cpp \
	computils.cpp \
	computils.h

examinerviewer_SOURCES = \
	examinerviewer.cpp \
	computils.cpp \
	computils.h

overlay_SOURCES = overlay.cpp

planeviewer_SOURCES = \
	planeviewer.cpp \
	computils.cpp \
	computils.h

walkviewer_SOURCES = \
	walkviewer.cpp \
	computils.cpp \
	computils.h

flyviewer_SOURCES = \
	flyviewer.cpp \
	computils.cpp \
	computils.h


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
	computils.cpp \
	computils.h \
	roster.cpp \
	renderarea.cpp \
	examinerviewer.cpp \
	planeviewer.cpp \
	walkviewer.cpp \
	flyviewer.cpp \
	lightsliderset.cpp \
	materialsliderset.cpp \
	materialsliderset2.cpp \
	transformsliderset.cpp \
	materiallist.cpp \
	materiallist2.cpp \
	grapheditor.cpp

noinst_PROGRAMS = renderarea examinerviewer overlay \
	planeviewer flyviewer walkviewer \
	$(SLIDERSETS) $(DIRECTIONALLIGHTEDITOR) $(MATERIALEDITOR) \
	$(MATERIALLIST) $(PRINTDIALOG)

############################################################################

computils.cpp: $(srcdir)/computils.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/computils.cpp )

computils.h: $(srcdir)/computils.h.in
	@( cd $(top_builddir); ./config.status --file=components/computils.h )

renderarea.cpp: $(srcdir)/renderarea.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/renderarea.cpp )

examinerviewer.cpp: $(srcdir)/examinerviewer.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/examinerviewer.cpp )

planeviewer.cpp: $(srcdir)/planeviewer.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/planeviewer.cpp )

walkviewer.cpp: $(srcdir)/walkviewer.cpp.in
	@( cd $(top_builddir); ./config.status --file=components/walkviewer.cpp )

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

############################################################################
