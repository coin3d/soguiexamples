BUILT_SOURCES = timersensor.cpp

noinst_PROGRAMS = timersensor

timersensor_SOURCES = timersensor.cpp


# Create Mac OS X application bundles.
app-bundles: all-am
	@case $(target_os) in darwin* ) \
	  echo "Making Mac OS X application bundles in sensors."; \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac


