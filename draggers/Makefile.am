BUILT_SOURCES = \
	jackdragger.cpp \
	translate1.cpp \
	translate2.cpp \
	dragpoint.cpp

noinst_PROGRAMS = jackdragger translate1 translate2 dragpoint

jackdragger_SOURCES = jackdragger.cpp
translate1_SOURCES = translate1.cpp
translate2_SOURCES = translate2.cpp
dragpoint_SOURCES = dragpoint.cpp

# Create Mac OS X application bundles.
app-bundles: all-am
	@case $(target_os) in darwin* ) \
	  echo "Making Mac OS X application bundles in draggers."; \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac

