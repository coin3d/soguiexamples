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


############################################################################

Moolah.cpp: $(srcdir)/Moolah.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20010914/Moolah.cpp )

calculator.cpp: $(srcdir)/calculator.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20010914/calculator.cpp )

coinhistory.cpp: $(srcdir)/coinhistory.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20010914/coinhistory.cpp )

kaos.cpp: $(srcdir)/kaos.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20010914/kaos.cpp )

rec.cpp: $(srcdir)/rec.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20010914/rec.cpp )

############################################################################
