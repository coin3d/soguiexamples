INCLUDES = -I$(top_srcdir)

noinst_PROGRAMS = \
	lorenz \
	nurbscurve \
	cubes

lorenz_SOURCES = lorenz.cpp star.h
nurbscurve_SOURCES = nurbscurve.cpp
cubes_SOURCES = cubes.cpp \
	Board.cpp Board.h GameLogic.cpp GameLogic.h Minimax.cpp Minimax.h \
	$(top_srcdir)/coin-competitions/TextureWriter.cpp

BUILT_SOURCES = \
	lorenz.cpp \
	nurbscurve.cpp \
	cubes.cpp


############################################################################

lorenz.cpp: $(srcdir)/lorenz.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20011005/lorenz.cpp )

nurbscurve.cpp: $(srcdir)/nurbscurve.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20011005/nurbscurve.cpp )

cubes.cpp: $(srcdir)/cubes.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20011005/cubes.cpp )

############################################################################
