BUILT_SOURCES = search.cpp raypick.cpp intersection.cpp

noinst_PROGRAMS = search raypick tesselate matrixtransform intersection ivcopy

search_SOURCES = search.cpp
raypick_SOURCES = raypick.cpp
tesselate_SOURCES = tesselate.cpp
matrixtransform_SOURCES = matrixtransform.cpp
intersection_SOURCES = intersection.cpp
ivcopy_SOURCES = ivcopy.cpp

# Create Mac OS X application bundles.
app-bundles: all-am
	@case $(target_os) in darwin* ) \
	  echo "Making Mac OS X application bundles in actions."; \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac

