############################################################################

BUILT_SOURCES = search.cpp raypick.cpp

noinst_PROGRAMS = search raypick tesselate matrixtransform

search_SOURCES = search.cpp
raypick_SOURCES = raypick.cpp
tesselate_SOURCES = tesselate.cpp
matrixtransform_SOURCES = matrixtransform.cpp

############################################################################

search.cpp: $(srcdir)/search.cpp.in
	@( cd $(top_builddir); ./config.status --file=actions/search.cpp)

raypick.cpp: $(srcdir)/raypick.cpp.in
	@( cd $(top_builddir); ./config.status --file=actions/raypick.cpp)

############################################################################
