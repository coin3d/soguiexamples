INCLUDES = -I$(top_srcdir)/coin-competitions

noinst_PROGRAMS = ballinthehoop flow typeomatic

ballinthehoop_SOURCES = ballinthehoop.cpp
flow_SOURCES = flow.cpp
typeomatic_SOURCES = typeomatic.cpp $(srcdir)/../strutils.cpp

BUILT_SOURCES = ballinthehoop.cpp flow.cpp typeomatic.cpp

# Create Mac OS X application bundles.
app-bundles: all-am
	@case $(target_os) in darwin* ) \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac

