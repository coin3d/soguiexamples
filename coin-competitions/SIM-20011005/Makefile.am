INCLUDES = -I$(top_srcdir)

noinst_PROGRAMS = \
	lorenz \
	nurbscurve \
	cubes

lorenz_SOURCES = lorenz.cpp star.h
nurbscurve_SOURCES = nurbscurve.cpp
cubes_SOURCES = cubes.cpp \
        Board.cpp Board.h GameLogic.cpp GameLogic.h Minimax.cpp Minimax.h \
        ../TextureWriter.cpp

BUILT_SOURCES = \
	lorenz.cpp \
	nurbscurve.cpp \
	cubes.cpp


############################################################################

lorenz.cpp: $(srcdir)/lorenz.cpp.in
	@( cd ../..; $(MAKE) built-sources )

nurbscurve.cpp: $(srcdir)/nurbscurve.cpp.in
	@( cd ../..; $(MAKE) built-sources )

cubes.cpp: $(srcdir)/cubes.cpp.in
	@( cd ../..; $(MAKE) built-sources )
