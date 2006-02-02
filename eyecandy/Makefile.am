noinst_PROGRAMS = \
	moirepatterns \
	juliaanim \
	mandelzoom \
	blob \
	simbuoy \
	toonshader 


moirepatterns_SOURCES = moirepatterns.cpp

juliaanim_SOURCES = juliaanim.cpp
EXTRA_juliaanim_SOURCES = stone42a.h stone42b.h sky10a.h sky10b.h

mandelzoom_SOURCES = mandelzoom.cpp
EXTRA_mandelzoom_SOURCES = stone42a.h stone42b.h sky10a.h sky10b.h

blob_SOURCES = blob.cpp

simbuoy_SOURCES = simbuoy.cpp

toonshader_SOURCES = toonshader.cpp

BUILT_SOURCES = \
	moirepatterns.cpp \
	juliaanim.cpp \
	mandelzoom.cpp \
	blob.cpp \
	simbuoy.cpp \
	toonshader.cpp

# Create Mac OS X application bundles.
app-bundles: all-am
	@case $(target_os) in darwin* ) \
	  echo "Making Mac OS X application bundles in eyecandy."; \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac


