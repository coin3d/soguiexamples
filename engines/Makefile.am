BUILT_SOURCES = \
	computebbox.cpp \
	computexfbbox.cpp.in

noinst_PROGRAMS = computebbox computexfbbox

computebbox_SOURCES = computebbox.cpp

computexfbbox_SOURCES = \
        computexfbbox.cpp \
        ComputeXfBoundingBox.cpp ComputeXfBoundingBox.h

# Create Mac OS X application bundles.
install-exec-local:
	@case $(target_os) in darwin* ) \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac

