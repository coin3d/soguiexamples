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
# misc rules for automatic Microsoft Windows packaging.
# main: `windows-packages'

windows-files:
	@if test -d windows; then :; else \
	  echo " mkdir windows"; \
	  mkdir windows; \
	fi
	@for file in $(top_srcdir)/packaging/windows/*.in; do \
	  basename=`echo $$file | sed 's%^.*/%%g; s%\.in$$%%'`; \
	  echo " config.status: generating windows/$$basename"; \
	  ./config.status --file=-:- >"windows/$$basename" <"$$file"; \
	done

windows-packages: windows-files
	@( cd windows; $(MAKE) VERSION=$(VERSION) )

# **************************************************************************
