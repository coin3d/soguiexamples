############################################################################

## So@Gui@RenderArea component
if HAVE_RENDERAREA
RENDERAREA = renderarea
renderarea_SOURCES = \
	renderarea.cpp \
	computils.cpp \
	computils.h
else
RENDERAREA =
renderarea_SOURCES =
endif

## So@Gui@ExaminerViewer component
if HAVE_EXAMINERVIEWER
EXAMINERVIEWER = examinerviewer
examinerviewer_SOURCES = \
	examinerviewer.cpp \
	computils.cpp \
	computils.h
else
EXAMINERVIEWER =
examinerviewer_SOURCES =
endif

## So@Gui@PlaneViewer component
if HAVE_PLANEVIEWER
PLANEVIEWER = planeviewer
planeviewer_SOURCES = \
	planeviewer.cpp \
	computils.cpp \
	computils.h
else
PLANEVIEWER =
planeviewer_SOURCES =
endif

## So@Gui@WalkViewer component
if HAVE_WALKVIEWER
WALKVIEWER = walkviewer
walkviewer_SOURCES = \
	walkviewer.cpp \
	computils.cpp \
	computils.h
else
WALKVIEWER =
walkviewer_SOURCES =
walkviewer_LDADD =
endif

## So@Gui@FlyViewer component
if HAVE_FLYVIEWER
FLYVIEWER = flyviewer
flyviewer_SOURCES = \
	flyviewer.cpp \
	computils.cpp \
	computils.h
else
FLYVIEWER =
flyviewer_SOURCES =
endif

## So@Gui@LightSliderSet component
if HAVE_LIGHTSLIDERSET
LIGHTSLIDERSET = lightsliderset
lightsliderset_SOURCES = \
	lightsliderset.cpp
else
LIGHTSLIDERSET =
lightsliderset_SOURCES =
endif

## So@Gui@MaterialSliderSet component
if HAVE_MATERIALSLIDERSET
MATERIALSLIDERSET = materialsliderset materialsliderset2
materialsliderset_SOURCES = \
	materialsliderset.cpp
materialsliderset2_SOURCES = \
	materialsliderset2.cpp
else
MATERIALSLIDERSET =
materialsliderset_SOURCES =
materialsliderset2_SOURCES =
endif

## So@Gui@TransformSliderSet component
if HAVE_TRANSFORMSLIDERSET
TRANSFORMSLIDERSET = transformsliderset
transformsliderset_SOURCES = \
	transformsliderset.cpp
else
TRANSFORMSLIDERSET =
transformsliderset_SOURCES =
endif

## So@Gui@DirectionalLightEditor component
if HAVE_DIRECTIONALLIGHTEDITOR
DIRECTIONALLIGHTEDITOR = directionallighteditor
directionallighteditor_SOURCES = \
	directionallighteditor.cpp
else
DIRECTIONALLIGHTEDITOR =
directionallighteditor_SOURCES =
endif

## So@Gui@MaterialEditor component
if HAVE_MATERIALEDITOR
MATERIALEDITOR = materialeditor
materialeditor_SOURCES = \
	materialeditor.cpp
else
MATERIALEDITOR =
materialeditor_SOURCES =
endif

## So@Gui@MaterialList component
if HAVE_MATERIALLIST
MATERIALLIST = materiallist materiallist2
materiallist_SOURCES = materiallist.cpp
materiallist2_SOURCES = materiallist2.cpp
else
MATERIALLIST =
materiallist_SOURCES =
materiallist2_SOURCES =
endif

## So@Gui@PrintDialog component
if HAVE_PRINTDIALOG
PRINTDIALOG = printdialog
printdialog_SOURCES = \
	printdialog.cpp
else
PRINTDIALOG =
printdialog_SOURCES =
endif

############################################################################

INCLUDES = -I$(top_builddir)/../src -I$(top_srcdir)/../src
VPATH = .:@srcdir@

BUILT_SOURCES = \
	computils.cpp \
	computils.h \
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
	materiallist2.cpp

noinst_PROGRAMS = $(RENDERAREA) $(EXAMINERVIEWER) \
	$(PLANEVIEWER) $(FLYVIEWER) $(WALKVIEWER) \
	$(LIGHTSLIDERSET) $(MATERIALSLIDERSET) $(TRANSFORMSLIDERSET) \
	$(DIRECTIONALLIGHTEDITOR) $(MATERIALEDITOR) \
	$(MATERIALLIST) $(PRINTDIALOG)

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

############################################################################
