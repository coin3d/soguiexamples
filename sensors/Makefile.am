BUILT_SOURCES = timersensor.cpp

noinst_PROGRAMS = timersensor

timersensor_SOURCES = timersensor.cpp


# Create Mac OS X application bundles.
install-exec-local:
	@case $(target_os) in darwin* ) \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac


