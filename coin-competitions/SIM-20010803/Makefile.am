noinst_PROGRAMS = \
	chart \
	plasmafun \
	stars

chart_SOURCES = chart.cpp
plasmafun_SOURCES = plasmafun.cpp

stars_SOURCES = stars.cpp
EXTRA_stars_SOURCES = star_raw.h envq_raw.h

BUILT_SOURCES = \
	chart.cpp \
	plasmafun.cpp \
	stars.cpp


############################################################################

chart.cpp: $(srcdir)/chart.cpp.in
	@( cd ..; $(MAKE) built-sources )

plasmafun.cpp: $(srcdir)/plasmafun.cpp.in
	@( cd ..; $(MAKE) built-sources )

stars.cpp: $(srcdir)/stars.cpp.in
	@( cd ..; $(MAKE) built-sources )

