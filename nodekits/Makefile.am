############################################################################
# conditional build

if HAVE_SMALLCHANGE
SMALLCHANGE_DEPENDENTS = scalemarker
else
SMALLCHANGE_DEPENDENTS = 
endif

############################################################################
# make from *.in files

BUILT_SOURCES = scalemarker.cpp wavekitdemo.cpp

############################################################################
# executables

noinst_PROGRAMS = wavekitdemo $(SMALLCHANGE_DEPENDENTS)

############################################################################
# source code dependencies

scalemarker_SOURCES = scalemarker.cpp

wavekitdemo_SOURCES = wavekitdemo.cpp WaveSurfaceKit.cpp WaveSurfaceKit.h

############################################################################


# Create Mac OS X application bundles.
app-bundles: all-am
	@case $(target_os) in darwin* ) \
	  echo "Making Mac OS X application bundles in nodekits."; \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac

