INCLUDES = -I$(top_srcdir)/coin-competitions

noinst_PROGRAMS = \
	smiley \
	plasmaball \
	styx \
	stars2

smiley_SOURCES = smiley.cpp
plasmaball_SOURCES = plasmaball.cpp
styx_SOURCES = styx.cpp

stars2_SOURCES = stars2.cpp
EXTRA_stars2_SOURCES = star_raw.h envq_raw.h

BUILT_SOURCES = \
	smiley.cpp \
	plasmaball.cpp \
	styx.cpp \
	stars2.cpp


############################################################################

smiley.cpp: $(srcdir)/smiley.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20010824/smiley.cpp )

plasmaball.cpp: $(srcdir)/plasmaball.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20010824/plasmaball.cpp )

styx.cpp: $(srcdir)/styx.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20010824/styx.cpp )

stars2.cpp: $(srcdir)/stars2.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20010824/stars2.cpp )

############################################################################
