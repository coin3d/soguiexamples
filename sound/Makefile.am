############################################################################
# make from *.in files

BUILT_SOURCES = audiocallback.cpp manysources.cpp

############################################################################
# executables

noinst_PROGRAMS = audiocallback manysources

############################################################################
# source code dependencies

audiocallback_SOURCES = audiocallback.cpp

manysources_SOURCES = manysources.cpp

############################################################################


# Create Mac OS X application bundles.
install-exec-local:
	@case $(target_os) in darwin* ) \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac

