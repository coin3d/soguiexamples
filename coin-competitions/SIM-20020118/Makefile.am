INCLUDES = -I$(top_srcdir)/coin-competitions

noinst_PROGRAMS = blocks

blocks_SOURCES = blocks.cpp

BUILT_SOURCES = blocks.cpp


############################################################################

blocks.cpp: $(srcdir)/blocks.cpp.in
	@( cd $(top_builddir); ./config.status --file=coin-competitions/SIM-20020118/blocks.cpp )
