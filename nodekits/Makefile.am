############################################################################
# conditional build

if HAVE_SMALLCHANGE
SMALLCHANGE_DEPENDENTS = scalemarker
else
SMALLCHANGE_DEPENDENTS = 
endif

############################################################################
# make from *.in files

BUILT_SOURCES = scalemarker.cpp wavekitdemo.cpp

############################################################################
# executables

noinst_PROGRAMS = wavekitdemo $(SMALLCHANGE_DEPENDENTS)

############################################################################
# source code dependencies

scalemarker_SOURCES = scalemarker.cpp

wavekitdemo_SOURCES = wavekitdemo.cpp WaveSurfaceKit.cpp WaveSurfaceKit.h

############################################################################
