BUILT_SOURCES = \
	drawstyle.cpp \
	material.cpp \
	selection.cpp \
	slideshow.cpp \
	sphere.cpp \
	spherecolor.cpp \
	rotation.cpp \
	scale.cpp \
	translation.cpp \
	transform.cpp \
	rotor.cpp \
	directionallight.cpp \
	pointlight.cpp \
	spotlight.cpp \
	lights.cpp \
	faceset.cpp \
	facesetindexed.cpp \
	quadmesh.cpp \
	trianglestripset.cpp \
	camera.cpp \
	blinker.cpp \
	texture.cpp \
	texture3.cpp \
	environment.cpp \
	atmospheric.cpp \
	shuttle.cpp \
	complexity.cpp \
	text2.cpp \
	text3.cpp \
	clipplane.cpp \
	levelofdetail.cpp \
	extselection.cpp \
	pointset.cpp \
	markerset.cpp \
	image.cpp \
	bigimage.cpp \
	textureunit.cpp \
	bumpmap.cpp \
	scenetexture.cpp \
	nurbssurface.cpp 


noinst_PROGRAMS = \
        drawstyle material selection slideshow sphere spherecolor \
        rotation scale translation transform rotor \
        directionallight pointlight spotlight lights \
        faceset facesetindexed quadmesh trianglestripset \
        camera blinker texture texture3 environment atmospheric shuttle \
        complexity text2 text3 clipplane levelofdetail extselection \
        pointset markerset image bigimage textureunit bumpmap \
	scenetexture nurbssurface

drawstyle_SOURCES = drawstyle.cpp
material_SOURCES = material.cpp
selection_SOURCES = selection.cpp
slideshow_SOURCES = slideshow.cpp
sphere_SOURCES = sphere.cpp
spherecolor_SOURCES = spherecolor.cpp
rotation_SOURCES = rotation.cpp
scale_SOURCES = scale.cpp
translation_SOURCES = translation.cpp
transform_SOURCES = transform.cpp
rotor_SOURCES = rotor.cpp
directionallight_SOURCES = directionallight.cpp
pointlight_SOURCES = pointlight.cpp
spotlight_SOURCES = spotlight.cpp
lights_SOURCES = lights.cpp
faceset_SOURCES = faceset.cpp
facesetindexed_SOURCES = facesetindexed.cpp
quadmesh_SOURCES = quadmesh.cpp
trianglestripset_SOURCES = trianglestripset.cpp
camera_SOURCES = camera.cpp
blinker_SOURCES = blinker.cpp
texture_SOURCES = texture.cpp
texture3_SOURCES = texture3.cpp
environment_SOURCES = environment.cpp
atmospheric_SOURCES = atmospheric.cpp
shuttle_SOURCES = shuttle.cpp
complexity_SOURCES = complexity.cpp
text2_SOURCES = text2.cpp
text3_SOURCES = text3.cpp
clipplane_SOURCES = clipplane.cpp
levelofdetail_SOURCES = levelofdetail.cpp
extselection_SOURCES = extselection.cpp
pointset_SOURCES = pointset.cpp
markerset_SOURCES = markerset.cpp
image_SOURCES = image.cpp
bigimage_SOURCES = bigimage.cpp
textureunit_SOURCES = textureunit.cpp
bumpmap_SOURCES = bumpmap.cpp
scenetexture_SOURCES = scenetexture.cpp
nurbssurface_SOURCES = nurbssurface.cpp


# Create Mac OS X application bundles.
app-bundles: all-am
	@case $(target_os) in darwin* ) \
	  echo "Making Mac OS X application bundles in nodes."; \
	  for i in $(noinst_PROGRAMS); do \
	    if test -f $$i; then $(soguiconfig) --build-app $$i; fi \
	  done;; \
	esac

