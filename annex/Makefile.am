############################################################################

BUILT_SOURCES = \
	hardcopy.cpp

noinst_PROGRAMS = hardcopy

hardcopy_SOURCES = hardcopy.cpp

############################################################################

hardcopy.cpp: $(srcdir)/hardcopy.cpp.in
	@( cd $(top_builddir); ./config.status --file=annex/hardcopy.cpp)

############################################################################
