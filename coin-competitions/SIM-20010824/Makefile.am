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
	@( cd ../..; $(MAKE) built-sources )

plasmaball.cpp: $(srcdir)/plasmaball.cpp.in
	@( cd ../..; $(MAKE) built-sources )

styx.cpp: $(srcdir)/styx.cpp.in
	@( cd ../..; $(MAKE) built-sources )

stars2.cpp: $(srcdir)/stars2.cpp.in
	@( cd ../..; $(MAKE) built-sources )

