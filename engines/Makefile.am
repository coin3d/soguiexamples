############################################################################

BUILT_SOURCES = \
	computebbox.cpp \
	computexfbbox.cpp.in

noinst_PROGRAMS = computebbox computexfbbox

computebbox_SOURCES = computebbox.cpp

computexfbbox_SOURCES = \
        computexfbbox.cpp \
        ComputeXfBoundingBox.cpp ComputeXfBoundingBox.h

############################################################################

computebbox.cpp: $(srcdir)/computebbox.cpp.in
	@( cd $(top_builddir); ./config.status --file=engines/computebbox.cpp)

computexfbbox.cpp: $(srcdir)/computexfbbox.cpp.in
	@( cd $(top_builddir); ./config.status --file=engines/computexfbbox.cpp)

############################################################################
