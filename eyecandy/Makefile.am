## SoGuiExamples/eyecandy/Makefile.am

noinst_PROGRAMS = \
	moirepatterns \
	juliaanim \
	mandelzoom \
	blob \
	simbuoy


moirepatterns_SOURCES = moirepatterns.cpp

juliaanim_SOURCES = juliaanim.cpp
EXTRA_juliaanim_SOURCES = stone42a.h stone42b.h sky10a.h sky10b.h

mandelzoom_SOURCES = mandelzoom.cpp
EXTRA_mandelzoom_SOURCES = stone42a.h stone42b.h sky10a.h sky10b.h

blob_SOURCES = blob.cpp

simbuoy_SOURCES = simbuoy.cpp

BUILT_SOURCES = \
	moirepatterns.cpp \
	juliaanim.cpp \
	mandelzoom.cpp \
	blob.cpp \
	simbuoy.cpp

############################################################################

moirepatterns.cpp: $(srcdir)/moirepatterns.cpp.in
	@( cd $(top_builddir); ./config.status --file=eyecandy/moirepatterns.cpp)

juliaanim.cpp: $(srcdir)/juliaanim.cpp.in
	@( cd $(top_builddir); ./config.status --file=eyecandy/juliaanim.cpp)

mandelzoom.cpp: $(srcdir)/mandelzoom.cpp.in
	@( cd $(top_builddir); ./config.status --file=eyecandy/mandelzoom.cpp)

blob.cpp: $(srcdir)/blob.cpp.in
	@( cd $(top_builddir); ./config.status --file=eyecandy/blob.cpp)

simbuoy.cpp: $(srcdir)/simbuoy.cpp.in
	@( cd $(top_builddir); ./config.status --file=eyecandy/simbuoy.cpp)

############################################################################
