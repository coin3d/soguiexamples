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
