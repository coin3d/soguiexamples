INCLUDES = -I$(top_srcdir)/coin-competitions

noinst_PROGRAMS = blocks

blocks_SOURCES = blocks.cpp

BUILT_SOURCES = blocks.cpp


############################################################################

# Create Mac OS X application bundles.
app-bundles: all-am
	@case $(target_os) in darwin* ) \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac
