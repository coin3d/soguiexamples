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
	@( cd ../..; $(MAKE) built-sources )

calculator.cpp: $(srcdir)/calculator.cpp.in
	@( cd ../..; $(MAKE) built-sources )

coinhistory.cpp: $(srcdir)/coinhistory.cpp.in
	@( cd ../..; $(MAKE) built-sources )

kaos.cpp: $(srcdir)/kaos.cpp.in
	@( cd ../..; $(MAKE) built-sources )

rec.cpp: $(srcdir)/rec.cpp.in
	@( cd ../..; $(MAKE) built-sources )
