############################################################################

BUILT_SOURCES = scalemarker.cpp

noinst_PROGRAMS = scalemarker

scalemarker_SOURCES = scalemarker.cpp ShapeScale.cpp ShapeScale.h

############################################################################

scalemarker.cpp: $(srcdir)/scalemarker.cpp.in
	@( cd $(top_builddir); ./config.status --file=nodekits/scalemarker.cpp)

############################################################################
