INCLUDES = -I$(top_srcdir)/coin-competitions

noinst_PROGRAMS = \
	25bc5bb \
	foo \
	shaker

25bc5bb_SOURCES = 25bc5bb.cpp coinlogo.h
foo_SOURCES = foo.cpp
shaker_SOURCES = shaker.cpp simlogo.h

BUILT_SOURCES = \
	25bc5bb.cpp \
	foo.cpp \
	shaker.cpp

# Create Mac OS X application bundles.
install-exec-local:
	@case $(target_os) in darwin* ) \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac


