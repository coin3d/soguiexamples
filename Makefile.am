############################################################################

ACLOCAL_AMFLAGS = -I cfg/m4

############################################################################

SUBDIRS = \
  . components eyecandy coin-competitions \
  actions draggers engines manipulators nodes sensors 

############################################################################

BUILT_SOURCES = \
	components/computils.cpp \
	components/computils.h \
	components/directionallighteditor.cpp \
	components/examinerviewer.cpp \
	components/overlay.cpp \
	components/flyviewer.cpp \
	components/lightsliderset.cpp \
	components/materialeditor.cpp \
	components/materiallist.cpp \
	components/materiallist2.cpp \
	components/materialsliderset.cpp \
	components/materialsliderset2.cpp \
	components/planeviewer.cpp \
	components/printdialog.cpp \
	components/renderarea.cpp \
	components/roster.cpp \
	components/transformsliderset.cpp \
	components/walkviewer.cpp \
	components/grapheditor.cpp \
	actions/raypick.cpp \
	actions/search.cpp \
	draggers/dragpoint.cpp \
	draggers/translate1.cpp \
	draggers/translate2.cpp \
	engines/computebbox.cpp \
	manipulators/pointlightmanip.cpp \
	manipulators/tabboxmanip.cpp \
	nodes/atmospheric.cpp \
	nodes/blinker.cpp \
	nodes/camera.cpp \
	nodes/clipplane.cpp \
	nodes/complexity.cpp \
	nodes/directionallight.cpp \
	nodes/drawstyle.cpp \
	nodes/environment.cpp \
	nodes/extselection.cpp \
	nodes/faceset.cpp \
	nodes/facesetindexed.cpp \
	nodes/levelofdetail.cpp \
	nodes/lights.cpp \
	nodes/material.cpp \
	nodes/markerset.cpp \
	nodes/pointlight.cpp \
	nodes/pointset.cpp \
	nodes/quadmesh.cpp \
	nodes/rotation.cpp \
	nodes/rotor.cpp \
	nodes/scale.cpp \
	nodes/selection.cpp \
	nodes/shuttle.cpp \
	nodes/slideshow.cpp \
	nodes/sphere.cpp \
	nodes/spherecolor.cpp \
	nodes/spotlight.cpp \
	nodes/text2.cpp \
	nodes/text3.cpp \
	nodes/texture.cpp \
	nodes/texture3.cpp \
	nodes/transform.cpp \
	nodes/translation.cpp \
	nodes/trianglestripset.cpp \
	sensors/timersensor.cpp \
	eyecandy/moirepatterns.cpp \
	eyecandy/juliaanim.cpp \
	eyecandy/mandelzoom.cpp \
	eyecandy/blob.cpp \
	eyecandy/simbuoy.cpp \
	coin-competitions/SIM-20010803/chart.cpp \
	coin-competitions/SIM-20010803/plasmafun.cpp \
	coin-competitions/SIM-20010803/stars.cpp \
	coin-competitions/SIM-20010824/stars2.cpp \
	coin-competitions/SIM-20010824/plasmaball.cpp \
	coin-competitions/SIM-20010824/styx.cpp \
	coin-competitions/SIM-20010824/smiley.cpp \
	coin-competitions/SIM-20010914/Moolah.cpp \
	coin-competitions/SIM-20010914/calculator.cpp \
	coin-competitions/SIM-20010914/coinhistory.cpp \
	coin-competitions/SIM-20010914/kaos.cpp \
	coin-competitions/SIM-20010914/rec.cpp \
	coin-competitions/SIM-20011005/lorenz.cpp \
	coin-competitions/SIM-20011005/nurbscurve.cpp \
	coin-competitions/SIM-20011005/cubes.cpp \
	coin-competitions/SIM-20011116/25bc5bb.cpp \
	coin-competitions/SIM-20011116/foo.cpp \
	coin-competitions/SIM-20011116/shaker.cpp

DISTCLEANFILES = $(BUILT_SOURCES)

noinst_DATA = $(BUILT_SOURCES)

built-sources: $(BUILT_SOURCES)

############################################################################
## sources in components/

components/computils.cpp: $(srcdir)/components/computils.cpp.in config.status
	@./config.status --file=$@

components/computils.h: $(srcdir)/components/computils.h.in config.status
	@./config.status --file=$@

components/directionallighteditor.cpp: \
  $(srcdir)/components/directionallighteditor.cpp.in config.status
	@./config.status --file=$@

components/examinerviewer.cpp: $(srcdir)/components/examinerviewer.cpp.in config.status
	@./config.status --file=$@

components/overlay.cpp: $(srcdir)/components/overlay.cpp.in config.status
	@./config.status --file=$@

components/grapheditor.cpp: $(srcdir)/components/grapheditor.cpp.in config.status
	@./config.status --file=$@

components/flyviewer.cpp: $(srcdir)/components/flyviewer.cpp.in config.status
	@./config.status --file=$@

components/lightsliderset.cpp: $(srcdir)/components/lightsliderset.cpp.in config.status
	@./config.status --file=$@

components/materialeditor.cpp: $(srcdir)/components/materialeditor.cpp.in config.status
	@./config.status --file=$@

components/materiallist.cpp: $(srcdir)/components/materiallist.cpp.in config.status
	@./config.status --file=$@

components/materiallist2.cpp: $(srcdir)/components/materiallist2.cpp.in config.status
	@./config.status --file=$@

components/materialsliderset.cpp: $(srcdir)/components/materialsliderset.cpp.in config.status
	@./config.status --file=$@

components/materialsliderset2.cpp: $(srcdir)/components/materialsliderset2.cpp.in config.status
	@./config.status --file=$@

components/planeviewer.cpp: $(srcdir)/components/planeviewer.cpp.in config.status
	@./config.status --file=$@

components/printdialog.cpp: $(srcdir)/components/printdialog.cpp.in config.status
	@./config.status --file=$@

components/renderarea.cpp: $(srcdir)/components/renderarea.cpp.in config.status
	@./config.status --file=$@

components/roster.cpp: $(srcdir)/components/roster.cpp.in config.status
	@./config.status --file=$@

components/transformsliderset.cpp: $(srcdir)/components/transformsliderset.cpp.in config.status
	@./config.status --file=$@

components/walkviewer.cpp: $(srcdir)/components/walkviewer.cpp.in config.status
	@./config.status --file=$@

############################################################################
## sources in actions/

actions/raypick.cpp: $(srcdir)/actions/raypick.cpp.in config.status
	@./config.status --file=$@

actions/search.cpp: $(srcdir)/actions/search.cpp.in config.status
	@./config.status --file=$@

############################################################################
## sources in draggers/

draggers/dragpoint.cpp: $(srcdir)/draggers/dragpoint.cpp.in config.status
	@./config.status --file=$@

draggers/translate1.cpp: $(srcdir)/draggers/translate1.cpp.in config.status
	@./config.status --file=$@

draggers/translate2.cpp: $(srcdir)/draggers/translate2.cpp.in config.status
	@./config.status --file=$@

############################################################################
## sources in engines/

engines/computebbox.cpp: $(srcdir)/engines/computebbox.cpp.in config.status
	@./config.status --file=$@

############################################################################
## sources in manipulators/

manipulators/pointlightmanip.cpp: $(srcdir)/manipulators/pointlightmanip.cpp.in config.status
	@./config.status --file=$@

manipulators/tabboxmanip.cpp: $(srcdir)/manipulators/tabboxmanip.cpp.in config.status
	@./config.status --file=$@

############################################################################
## sources in nodes/

nodes/atmospheric.cpp: $(srcdir)/nodes/atmospheric.cpp.in config.status
	@./config.status --file=$@

nodes/blinker.cpp: $(srcdir)/nodes/blinker.cpp.in config.status
	@./config.status --file=$@

nodes/camera.cpp: $(srcdir)/nodes/camera.cpp.in config.status
	@./config.status --file=$@

nodes/clipplane.cpp: $(srcdir)/nodes/clipplane.cpp.in config.status
	@./config.status --file=$@

nodes/complexity.cpp: $(srcdir)/nodes/complexity.cpp.in config.status
	@./config.status --file=$@

nodes/directionallight.cpp: $(srcdir)/nodes/directionallight.cpp.in config.status
	@./config.status --file=$@

nodes/drawstyle.cpp: $(srcdir)/nodes/drawstyle.cpp.in config.status
	@./config.status --file=$@

nodes/environment.cpp: $(srcdir)/nodes/environment.cpp.in config.status
	@./config.status --file=$@

nodes/extselection.cpp: $(srcdir)/nodes/extselection.cpp.in config.status
	@./config.status --file=$@

nodes/faceset.cpp: $(srcdir)/nodes/faceset.cpp.in config.status
	@./config.status --file=$@

nodes/facesetindexed.cpp: $(srcdir)/nodes/facesetindexed.cpp.in config.status
	@./config.status --file=$@

nodes/levelofdetail.cpp: $(srcdir)/nodes/levelofdetail.cpp.in config.status
	@./config.status --file=$@

nodes/lights.cpp: $(srcdir)/nodes/lights.cpp.in config.status
	@./config.status --file=$@

nodes/material.cpp: $(srcdir)/nodes/material.cpp.in config.status
	@./config.status --file=$@

nodes/markerset.cpp: $(srcdir)/nodes/markerset.cpp.in config.status
	@./config.status --file=$@

nodes/pointlight.cpp: $(srcdir)/nodes/pointlight.cpp.in config.status
	@./config.status --file=$@

nodes/pointset.cpp: $(srcdir)/nodes/pointset.cpp.in config.status
	@./config.status --file=$@

nodes/quadmesh.cpp: $(srcdir)/nodes/quadmesh.cpp.in config.status
	@./config.status --file=$@

nodes/rotation.cpp: $(srcdir)/nodes/rotation.cpp.in config.status
	@./config.status --file=$@

nodes/rotor.cpp: $(srcdir)/nodes/rotor.cpp.in config.status
	@./config.status --file=$@

nodes/scale.cpp: $(srcdir)/nodes/scale.cpp.in config.status
	@./config.status --file=$@

nodes/selection.cpp: $(srcdir)/nodes/selection.cpp.in config.status
	@./config.status --file=$@

nodes/shuttle.cpp: $(srcdir)/nodes/shuttle.cpp.in config.status
	@./config.status --file=$@

nodes/slideshow.cpp: $(srcdir)/nodes/slideshow.cpp.in config.status
	@./config.status --file=$@

nodes/sphere.cpp: $(srcdir)/nodes/sphere.cpp.in config.status
	@./config.status --file=$@

nodes/spherecolor.cpp: $(srcdir)/nodes/spherecolor.cpp.in config.status
	@./config.status --file=$@

nodes/spotlight.cpp: $(srcdir)/nodes/spotlight.cpp.in config.status
	@./config.status --file=$@

nodes/text2.cpp: $(srcdir)/nodes/text2.cpp.in config.status
	@./config.status --file=$@

nodes/text3.cpp: $(srcdir)/nodes/text3.cpp.in config.status
	@./config.status --file=$@

nodes/texture.cpp: $(srcdir)/nodes/texture.cpp.in config.status
	@./config.status --file=$@

nodes/texture3.cpp: $(srcdir)/nodes/texture3.cpp.in config.status
	@./config.status --file=$@

nodes/transform.cpp: $(srcdir)/nodes/transform.cpp.in config.status
	@./config.status --file=$@

nodes/translation.cpp: $(srcdir)/nodes/translation.cpp.in config.status
	@./config.status --file=$@

nodes/trianglestripset.cpp: $(srcdir)/nodes/trianglestripset.cpp.in config.status
	@./config.status --file=$@

############################################################################
## sources in sensors/

sensors/timersensor.cpp: $(srcdir)/sensors/timersensor.cpp.in config.status
	@./config.status --file=$@

############################################################################
## sources in eyecandy/

eyecandy/moirepatterns.cpp: $(srcdir)/eyecandy/moirepatterns.cpp.in config.status
	@./config.status --file=$@

eyecandy/juliaanim.cpp: $(srcdir)/eyecandy/juliaanim.cpp.in config.status
	@./config.status --file=$@

eyecandy/mandelzoom.cpp: $(srcdir)/eyecandy/mandelzoom.cpp.in config.status
	@./config.status --file=$@

eyecandy/blob.cpp: $(srcdir)/eyecandy/blob.cpp.in config.status
	@./config.status --file=$@

eyecandy/simbuoy.cpp: $(srcdir)/eyecandy/simbuoy.cpp.in config.status
	@./config.status --file=$@

############################################################################
## sources in coin-competitions/SIM-20010803/

coin-competitions/SIM-20010803/chart.cpp: $(srcdir)/coin-competitions/SIM-20010803/chart.cpp.in config.status
	@./config.status --file=$@

coin-competitions/SIM-20010803/plasmafun.cpp: $(srcdir)/coin-competitions/SIM-20010803/plasmafun.cpp.in config.status
	@./config.status --file=$@

coin-competitions/SIM-20010803/stars.cpp: $(srcdir)/coin-competitions/SIM-20010803/stars.cpp.in config.status
	@./config.status --file=$@

############################################################################
## sources in coin-competitions/SIM-20010824/

coin-competitions/SIM-20010824/stars2.cpp: $(srcdir)/coin-competitions/SIM-20010824/stars2.cpp.in config.status
	@./config.status --file=$@

coin-competitions/SIM-20010824/smiley.cpp: $(srcdir)/coin-competitions/SIM-20010824/smiley.cpp.in config.status
	@./config.status --file=$@

coin-competitions/SIM-20010824/styx.cpp: $(srcdir)/coin-competitions/SIM-20010824/styx.cpp.in config.status
	@./config.status --file=$@

coin-competitions/SIM-20010824/plasmaball.cpp: $(srcdir)/coin-competitions/SIM-20010824/plasmaball.cpp.in config.status
	@./config.status --file=$@

############################################################################
## sources in coin-competitions/SIM-20010914/

coin-competitions/SIM-20010914/Moolah.cpp: $(srcdir)/coin-competitions/SIM-20010914/Moolah.cpp.in config.status
	@./config.status --file=$@

coin-competitions/SIM-20010914/calculator.cpp: $(srcdir)/coin-competitions/SIM-20010914/calculator.cpp.in config.status
	@./config.status --file=$@

coin-competitions/SIM-20010914/coinhistory.cpp: $(srcdir)/coin-competitions/SIM-20010914/coinhistory.cpp.in config.status
	@./config.status --file=$@

coin-competitions/SIM-20010914/kaos.cpp: $(srcdir)/coin-competitions/SIM-20010914/kaos.cpp.in config.status
	@./config.status --file=$@

coin-competitions/SIM-20010914/rec.cpp: $(srcdir)/coin-competitions/SIM-20010914/rec.cpp.in config.status
	@./config.status --file=$@

############################################################################
## sources in coin-competitions/SIM-20011005/

coin-competitions/SIM-20011005/lorenz.cpp: $(srcdir)/coin-competitions/SIM-20011005/lorenz.cpp.in config.status
	@./config.status --file=$@

coin-competitions/SIM-20011005/nurbscurve.cpp: $(srcdir)/coin-competitions/SIM-20011005/nurbscurve.cpp.in config.status
	@./config.status --file=$@

coin-competitions/SIM-20011005/cubes.cpp: $(srcdir)/coin-competitions/SIM-20011005/cubes.cpp.in config.status
	@./config.status --file=$@

############################################################################
## sources in coin-competitions/SIM-20011116/

coin-competitions/SIM-20011116/25bc5bb.cpp: $(srcdir)/coin-competitions/SIM-20011116/25bc5bb.cpp.in config.status
	@./config.status --file=$@

coin-competitions/SIM-20011116/foo.cpp: $(srcdir)/coin-competitions/SIM-20011116/foo.cpp.in config.status
	@./config.status --file=$@

coin-competitions/SIM-20011116/shaker.cpp: $(srcdir)/coin-competitions/SIM-20011116/shaker.cpp.in config.status
	@./config.status --file=$@

############################################################################
