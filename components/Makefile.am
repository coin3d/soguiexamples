############################################################################

## So@Gui@Roster component
if HAVE_ROSTER
ROSTER = roster
else
ROSTER =
endif

roster_SOURCES = \
	roster.cpp

## So@Gui@RenderArea component
if HAVE_RENDERAREA
RENDERAREA = renderarea
else
RENDERAREA =
endif

renderarea_SOURCES = \
	renderarea.cpp \
	computils.cpp \
	computils.h

## So@Gui@ExaminerViewer component
if HAVE_EXAMINERVIEWER
EXAMINERVIEWER = examinerviewer overlay
else
EXAMINERVIEWER =
endif

examinerviewer_SOURCES = \
	examinerviewer.cpp \
	computils.cpp \
	computils.h

overlay_SOURCES = \
	overlay.cpp \
	computils.cpp \
	computils.h

## So@Gui@PlaneViewer component
if HAVE_PLANEVIEWER
PLANEVIEWER = planeviewer
else
PLANEVIEWER =
endif

planeviewer_SOURCES = \
	planeviewer.cpp \
	computils.cpp \
	computils.h

## So@Gui@WalkViewer component
if HAVE_WALKVIEWER
WALKVIEWER = walkviewer
else
WALKVIEWER =
endif

walkviewer_SOURCES = \
	walkviewer.cpp \
	computils.cpp \
	computils.h

## So@Gui@FlyViewer component
if HAVE_FLYVIEWER
FLYVIEWER = flyviewer
else
FLYVIEWER =
endif

flyviewer_SOURCES = \
	flyviewer.cpp \
	computils.cpp \
	computils.h

## So@Gui@CustomViewer component
if HAVE_CUSTOMVIEWER
CUSTOMVIEWER = customviewer
else
CUSTOMVIEWER =
endif

customviewer_SOURCES = \
	customviewer.cpp \
	computils.cpp \
	computils.h

## So@Gui@LightSliderSet component
if HAVE_LIGHTSLIDERSET
LIGHTSLIDERSET = lightsliderset
else
LIGHTSLIDERSET =
endif

lightsliderset_SOURCES = \
	lightsliderset.cpp

## So@Gui@MaterialSliderSet component
if HAVE_MATERIALSLIDERSET
MATERIALSLIDERSET = materialsliderset materialsliderset2
else
MATERIALSLIDERSET =
endif

materialsliderset_SOURCES = \
	materialsliderset.cpp
materialsliderset2_SOURCES = \
	materialsliderset2.cpp

## So@Gui@TransformSliderSet component
if HAVE_TRANSFORMSLIDERSET
TRANSFORMSLIDERSET = transformsliderset
else
TRANSFORMSLIDERSET =
endif

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

## So@Gui@GraphEditor component
if HAVE_GRAPHEDITOR
GRAPHEDITOR = grapheditor
else
GRAPHEDITOR =
endif

grapheditor_SOURCES = grapheditor.cpp \
	computils.cpp \
	computils.h

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
	customviewer.cpp \
	lightsliderset.cpp \
	materialsliderset.cpp \
	materialsliderset2.cpp \
	transformsliderset.cpp \
	materiallist.cpp \
	materiallist2.cpp \
	grapheditor.cpp

noinst_PROGRAMS = $(ROSTER) $(RENDERAREA) $(EXAMINERVIEWER) \
	$(PLANEVIEWER) $(FLYVIEWER) $(WALKVIEWER) $(CUSTOMVIEWER) \
	$(LIGHTSLIDERSET) $(MATERIALSLIDERSET) $(TRANSFORMSLIDERSET) \
	$(DIRECTIONALLIGHTEDITOR) $(MATERIALEDITOR) \
	$(MATERIALLIST) $(PRINTDIALOG) $(GRAPHEDITOR)

############################################################################

computils.cpp: $(srcdir)/computils.cpp.in
	@( cd ..; $(MAKE) built-sources )

computils.h: $(srcdir)/computils.h.in
	@( cd ..; $(MAKE) built-sources )

renderarea.cpp: $(srcdir)/renderarea.cpp.in
	@( cd ..; $(MAKE) built-sources )

examinerviewer.cpp: $(srcdir)/examinerviewer.cpp.in
	@( cd ..; $(MAKE) built-sources )

planeviewer.cpp: $(srcdir)/planeviewer.cpp.in
	@( cd ..; $(MAKE) built-sources )

walkviewer.cpp: $(srcdir)/walkviewer.cpp.in
	@( cd ..; $(MAKE) built-sources )

flyviewer.cpp: $(srcdir)/flyviewer.cpp.in
	@( cd ..; $(MAKE) built-sources )

customviewer.cpp: $(srcdir)/customviewer.cpp.in
	@( cd ..; $(MAKE) built-sources )

lightsliderset.cpp: $(srcdir)/lightsliderset.cpp.in
	@( cd ..; $(MAKE) built-sources )

materialsliderset.cpp: $(srcdir)/materialsliderset.cpp.in
	@( cd ..; $(MAKE) built-sources )

materialsliderset2.cpp: $(srcdir)/materialsliderset2.cpp.in
	@( cd ..; $(MAKE) built-sources )

transformsliderset.cpp: $(srcdir)/transformsliderset.cpp.in
	@( cd ..; $(MAKE) built-sources )

materiallist.cpp: $(srcdir)/materiallist.cpp.in
	@( cd ..; $(MAKE) built-sources )

materiallist2.cpp: $(srcdir)/materiallist2.cpp.in
	@( cd ..; $(MAKE) built-sources )

grapheditor.cpp: $(srcdir)/grapheditor.cpp.in
	@( cd ..; $(MAKE) built-sources )

############################################################################
