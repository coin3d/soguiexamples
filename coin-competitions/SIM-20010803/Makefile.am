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
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20010803/chart.cpp )

plasmafun.cpp: $(srcdir)/plasmafun.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20010803/plasmafun.cpp )

stars.cpp: $(srcdir)/stars.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20010803/stars.cpp )

############################################################################
