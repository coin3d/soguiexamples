INCLUDES = -I$(top_srcdir)/coin-competitions

noinst_PROGRAMS = \
	smiley \
	plasmaball \
	styx \
	stars2

smiley_SOURCES = smiley.cpp
plasmaball_SOURCES = plasmaball.cpp
styx_SOURCES = styx.cpp

stars2_SOURCES = stars2.cpp
EXTRA_stars2_SOURCES = star_raw.h envq_raw.h

BUILT_SOURCES = \
	smiley.cpp \
	plasmaball.cpp \
	styx.cpp \
	stars2.cpp

# Create Mac OS X application bundles.
app-bundles: all-am
	@case $(target_os) in darwin* ) \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac

