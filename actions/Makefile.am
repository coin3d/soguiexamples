############################################################################

BUILT_SOURCES = search.cpp raypick.cpp

noinst_PROGRAMS = search raypick

search_SOURCES = search.cpp
raypick_SOURCES = raypick.cpp

############################################################################

search.cpp: $(srcdir)/search.cpp.in
	@( cd ..; $(MAKE) built-sources )

raypick.cpp: $(srcdir)/raypick.cpp.in
	@( cd ..; $(MAKE) built-sources )

############################################################################
