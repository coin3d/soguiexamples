############################################################################

BUILT_SOURCES = \
	translate1.cpp \
	translate2.cpp \
	dragpoint.cpp

noinst_PROGRAMS = translate1 translate2 dragpoint

translate1_SOURCES = translate1.cpp
translate2_SOURCES = translate2.cpp
dragpoint_SOURCES = dragpoint.cpp

############################################################################

translate1.cpp: $(srcdir)/translate1.cpp.in
	@( cd $(top_builddir); ./config.status --file=draggers/translate1.cpp )

translate2.cpp: $(srcdir)/translate2.cpp.in
	@( cd $(top_builddir); ./config.status --file=draggers/translate2.cpp )

dragpoint.cpp: $(srcdir)/dragpoint.cpp.in
	@( cd $(top_builddir); ./config.status --file=draggers/dragpoint.cpp )

############################################################################
