BUILT_SOURCES = \
	hardcopy.cpp

noinst_PROGRAMS = hardcopy rawhardcopy

hardcopy_SOURCES = hardcopy.cpp

rawhardcopy_SOURCES = rawhardcopy.cpp

# Create Mac OS X application bundles.
app-bundles: all-am
	@case $(target_os) in darwin* ) \
	  echo "Making Mac OS X application bundles in annex."; \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac

