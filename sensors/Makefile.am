############################################################################

BUILT_SOURCES = timersensor.cpp

noinst_PROGRAMS = timersensor

timersensor_SOURCES = timersensor.cpp

############################################################################

timersensor.cpp: $(srcdir)/timersensor.cpp.in
	@( cd $(top_builddir); ./config.status --file=sensors/timersensor.cpp)

############################################################################
