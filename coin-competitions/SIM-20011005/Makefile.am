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

# Create Mac OS X application bundles.
app-bundles: all-am
	@case $(target_os) in darwin* ) \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac

