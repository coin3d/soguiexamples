INCLUDES = -I$(top_srcdir)/coin-competitions

noinst_PROGRAMS = \
	25bc5bb \
	foo \
	shaker

25bc5bb_SOURCES = 25bc5bb.cpp coinlogo.h
foo_SOURCES = foo.cpp
shaker_SOURCES = shaker.cpp simlogo.h

BUILT_SOURCES = \
	25bc5bb.cpp \
	foo.cpp \
	shaker.cpp


############################################################################

25bc5bb.cpp: $(srcdir)/25bc5bb.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20011116/25bc5bb.cpp )

foo.cpp: $(srcdir)/foo.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20011116/foo.cpp )

shaker.cpp: $(srcdir)/shaker.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20011116/shaker.cpp )

############################################################################
