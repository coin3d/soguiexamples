noinst_PROGRAMS = \
	chart \
	plasmafun \
	stars

chart_SOURCES = chart.cpp
plasmafun_SOURCES = plasmafun.cpp

stars_SOURCES = stars.cpp
EXTRA_stars_SOURCES = star_raw.h envq_raw.h

BUILT_SOURCES = \
	chart.cpp \
	plasmafun.cpp \
	stars.cpp

# Create Mac OS X application bundles.
install-exec-local:
	@case $(target_os) in darwin* ) \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac

