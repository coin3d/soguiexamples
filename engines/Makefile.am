############################################################################

BUILT_SOURCES = \
	computebbox.cpp

noinst_PROGRAMS = computebbox

computebbox_SOURCES = computebbox.cpp

############################################################################

computebbox.cpp: $(srcdir)/computebbox.cpp.in
	@( cd $(top_builddir); ./config.status --file=engines/computebbox.cpp)

############################################################################
