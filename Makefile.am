# **************************************************************************
# Conditionally build SimVoleon examples if the library was found by the
# configure process.

if HAVE_SIMVOLEON
VOLUMERENDERINGDIR = volumerendering
else
VOLUMERENDERINGDIR = 
endif

# **************************************************************************

SUBDIRS = \
  . components eyecandy coin-competitions annex \
  actions draggers engines manipulators nodes sensors nodekits \
  $(VOLUMERENDERINGDIR)

# **************************************************************************
