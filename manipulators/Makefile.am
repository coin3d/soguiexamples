############################################################################

BUILT_SOURCES = pointlightmanip.cpp tabboxmanip.cpp

noinst_PROGRAMS = pointlightmanip tabboxmanip

pointlightmanip_SOURCES = pointlightmanip.cpp
tabboxmanip_SOURCES = tabboxmanip.cpp

############################################################################

pointlightmanip.cpp: $(srcdir)/pointlightmanip.cpp.in
	@( cd $(top_builddir); ./config.status --file=manipulators/pointlightmanip.cpp)

tabboxmanip.cpp: $(srcdir)/tabboxmanip.cpp.in
	@( cd $(top_builddir); ./config.status --file=manipulators/tabboxmanip.cpp)

############################################################################
