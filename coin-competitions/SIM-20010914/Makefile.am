noinst_PROGRAMS = \
	moolah \
	calculator \
	coinhistory \
	kaos \
	rec

calculator_SOURCES = calculator.cpp
coinhistory_SOURCES = coinhistory.cpp
kaos_SOURCES = kaos.cpp
rec_SOURCES = rec.cpp

moolah_SOURCES = \
	Moolah.cpp \
	MooExecutive.cpp MooExecutive.h \
	MooList.cpp MooList.h \
	MooOut.cpp MooOut.h \
	MooString.cpp MooString.h \
	MooTokenizer.cpp MooTokenizer.h \
	font.h


BUILT_SOURCES = \
	Moolah.cpp \
	calculator.cpp \
	coinhistory.cpp \
	kaos.cpp \
	rec.cpp

# Create Mac OS X application bundles.
app-bundles: all-am
	@case $(target_os) in darwin* ) \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac

