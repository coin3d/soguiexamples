BUILT_SOURCES = pointlightmanip.cpp tabboxmanip.cpp

noinst_PROGRAMS = pointlightmanip tabboxmanip

pointlightmanip_SOURCES = pointlightmanip.cpp
tabboxmanip_SOURCES = tabboxmanip.cpp

# Create Mac OS X application bundles.
app-bundles: all-am
	@case $(target_os) in darwin* ) \
	  echo "Making Mac OS X application bundles in manipulators."; \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac

