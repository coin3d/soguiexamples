############################################################################

BUILT_SOURCES = scalemarker.cpp wavekitdemo.cpp

noinst_PROGRAMS = scalemarker wavekitdemo

scalemarker_SOURCES = scalemarker.cpp ShapeScale.cpp ShapeScale.h

wavekitdemo_SOURCES = wavekitdemo.cpp WaveSurfaceKit.cpp WaveSurfaceKit.h

############################################################################

scalemarker.cpp: $(srcdir)/scalemarker.cpp.in
	@( cd $(top_builddir); ./config.status --file=nodekits/scalemarker.cpp)

wavekitdemo.cpp: $(srcdir)/wavekitdemo.cpp.in
	@( cd $(top_builddir); ./config.status --file=nodekits/wavekitdemo.cpp)

############################################################################
