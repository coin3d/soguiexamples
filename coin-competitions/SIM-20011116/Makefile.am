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
	@( cd ../..; $(MAKE) built-sources )

foo.cpp: $(srcdir)/foo.cpp.in
	@( cd ../..; $(MAKE) built-sources )

shaker.cpp: $(srcdir)/shaker.cpp.in
	@( cd ../..; $(MAKE) built-sources )
