INCLUDES = -I$(top_srcdir)/coin-competitions

noinst_PROGRAMS = ballinthehoop flow typeomatic

ballinthehoop_SOURCES = ballinthehoop.cpp
flow_SOURCES = flow.cpp
typeomatic_SOURCES = typeomatic.cpp ../strutils.cpp

BUILT_SOURCES = ballinthehoop.cpp flow.cpp typeomatic.cpp

############################################################################

ballinthehoop.cpp: $(srcdir)/ballinthehoop.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20020503/ballinthehoop.cpp )

flow.cpp: $(srcdir)/flow.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20020503/flow.cpp )

typeomatic.cpp: $(srcdir)/typeomatic.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20020503/typeomatic.cpp )
