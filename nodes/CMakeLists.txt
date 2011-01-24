INCLUDE_DIRECTORIES(./)
SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/nodes)
INCLUDE_DIRECTORIES(${CONF_FILE_DIR})

#atmospheric example
CONFIGURE_FILE(atmospheric.cpp.in ${CONF_FILE_DIR}/atmospheric.cpp)
SET(atmospheric_SOURCE ${CONF_FILE_DIR}/atmospheric.cpp)
ADD_EXECUTABLE(atmospheric ${atmospheric_SOURCE})
TARGET_LINK_LIBRARIES(atmospheric ${LINK_LIBRARY})

#bigimage example
CONFIGURE_FILE(bigimage.cpp.in ${CONF_FILE_DIR}/bigimage.cpp)
SET(bigimage_SOURCE ${CONF_FILE_DIR}/bigimage.cpp)
ADD_EXECUTABLE(bigimage ${bigimage_SOURCE})
TARGET_LINK_LIBRARIES(bigimage ${LINK_LIBRARY})

#blinker example
CONFIGURE_FILE(blinker.cpp.in ${CONF_FILE_DIR}/blinker.cpp)
SET(blinker_SOURCE ${CONF_FILE_DIR}/blinker.cpp)
ADD_EXECUTABLE(blinker ${blinker_SOURCE})
TARGET_LINK_LIBRARIES(blinker ${LINK_LIBRARY})

#bumpmap example
CONFIGURE_FILE(bumpmap.cpp.in ${CONF_FILE_DIR}/bumpmap.cpp)
SET(bumpmap_SOURCE ${CONF_FILE_DIR}/bumpmap.cpp)
ADD_EXECUTABLE(bumpmap ${bumpmap_SOURCE})
TARGET_LINK_LIBRARIES(bumpmap ${LINK_LIBRARY})

#camera example
CONFIGURE_FILE(camera.cpp.in ${CONF_FILE_DIR}/camera.cpp)
SET(camera_SOURCE ${CONF_FILE_DIR}/camera.cpp)
ADD_EXECUTABLE(camera ${camera_SOURCE})
TARGET_LINK_LIBRARIES(camera ${LINK_LIBRARY})

#clipplane example
CONFIGURE_FILE(clipplane.cpp.in ${CONF_FILE_DIR}/clipplane.cpp)
SET(clipplane_SOURCE ${CONF_FILE_DIR}/clipplane.cpp)
ADD_EXECUTABLE(clipplane ${clipplane_SOURCE})
TARGET_LINK_LIBRARIES(clipplane ${LINK_LIBRARY})

#complexity example
CONFIGURE_FILE(complexity.cpp.in ${CONF_FILE_DIR}/complexity.cpp)
SET(complexity_SOURCE ${CONF_FILE_DIR}/complexity.cpp)
ADD_EXECUTABLE(complexity ${complexity_SOURCE})
TARGET_LINK_LIBRARIES(complexity ${LINK_LIBRARY})

#directionallight example
CONFIGURE_FILE(directionallight.cpp.in ${CONF_FILE_DIR}/directionallight.cpp)
SET(directionallight_SOURCE ${CONF_FILE_DIR}/directionallight.cpp)
ADD_EXECUTABLE(directionallight ${directionallight_SOURCE})
TARGET_LINK_LIBRARIES(directionallight ${LINK_LIBRARY})

#drawstyle example
CONFIGURE_FILE(drawstyle.cpp.in ${CONF_FILE_DIR}/drawstyle.cpp)
SET(drawstyle_SOURCE ${CONF_FILE_DIR}/drawstyle.cpp)
ADD_EXECUTABLE(drawstyle ${drawstyle_SOURCE})
TARGET_LINK_LIBRARIES(drawstyle ${LINK_LIBRARY})

#environment example
CONFIGURE_FILE(environment.cpp.in ${CONF_FILE_DIR}/environment.cpp)
SET(environment_SOURCE ${CONF_FILE_DIR}/environment.cpp)
ADD_EXECUTABLE(environment ${environment_SOURCE})
TARGET_LINK_LIBRARIES(environment ${LINK_LIBRARY})

#extselection example
CONFIGURE_FILE(extselection.cpp.in ${CONF_FILE_DIR}/extselection.cpp)
SET(extselection_SOURCE ${CONF_FILE_DIR}/extselection.cpp)
ADD_EXECUTABLE(extselection ${extselection_SOURCE})
TARGET_LINK_LIBRARIES(extselection ${LINK_LIBRARY})

#faceset example
CONFIGURE_FILE(faceset.cpp.in ${CONF_FILE_DIR}/faceset.cpp)
SET(faceset_SOURCE ${CONF_FILE_DIR}/faceset.cpp)
ADD_EXECUTABLE(faceset ${faceset_SOURCE})
TARGET_LINK_LIBRARIES(faceset ${LINK_LIBRARY})

#facesetindexed example
CONFIGURE_FILE(facesetindexed.cpp.in ${CONF_FILE_DIR}/facesetindexed.cpp)
SET(facesetindexed_SOURCE ${CONF_FILE_DIR}/facesetindexed.cpp)
ADD_EXECUTABLE(facesetindexed ${facesetindexed_SOURCE})
TARGET_LINK_LIBRARIES(facesetindexed ${LINK_LIBRARY})

#image example
CONFIGURE_FILE(image.cpp.in ${CONF_FILE_DIR}/image.cpp)
SET(image_SOURCE ${CONF_FILE_DIR}/image.cpp)
ADD_EXECUTABLE(image ${image_SOURCE})
TARGET_LINK_LIBRARIES(image ${LINK_LIBRARY})

#levelofdetail example
CONFIGURE_FILE(levelofdetail.cpp.in ${CONF_FILE_DIR}/levelofdetail.cpp)
SET(levelofdetail_SOURCE ${CONF_FILE_DIR}/levelofdetail.cpp)
ADD_EXECUTABLE(levelofdetail ${levelofdetail_SOURCE})
TARGET_LINK_LIBRARIES(levelofdetail ${LINK_LIBRARY})

#lights example
CONFIGURE_FILE(lights.cpp.in ${CONF_FILE_DIR}/lights.cpp)
SET(lights_SOURCE ${CONF_FILE_DIR}/lights.cpp)
ADD_EXECUTABLE(lights ${lights_SOURCE})
TARGET_LINK_LIBRARIES(lights ${LINK_LIBRARY})

#markerset example
CONFIGURE_FILE(markerset.cpp.in ${CONF_FILE_DIR}/markerset.cpp)
SET(markerset_SOURCE ${CONF_FILE_DIR}/markerset.cpp)
ADD_EXECUTABLE(markerset ${markerset_SOURCE})
TARGET_LINK_LIBRARIES(markerset ${LINK_LIBRARY})

#material example
CONFIGURE_FILE(material.cpp.in ${CONF_FILE_DIR}/material.cpp)
SET(material_SOURCE ${CONF_FILE_DIR}/material.cpp)
ADD_EXECUTABLE(material ${material_SOURCE})
TARGET_LINK_LIBRARIES(material ${LINK_LIBRARY})

#nurbssurface example
CONFIGURE_FILE(nurbssurface.cpp.in ${CONF_FILE_DIR}/nurbssurface.cpp)
SET(nurbssurface_SOURCE ${CONF_FILE_DIR}/nurbssurface.cpp)
ADD_EXECUTABLE(nurbssurface ${nurbssurface_SOURCE})
TARGET_LINK_LIBRARIES(nurbssurface ${LINK_LIBRARY})

#pointlight example
CONFIGURE_FILE(pointlight.cpp.in ${CONF_FILE_DIR}/pointlight.cpp)
SET(pointlight_SOURCE ${CONF_FILE_DIR}/pointlight.cpp)
ADD_EXECUTABLE(pointlight ${pointlight_SOURCE})
TARGET_LINK_LIBRARIES(pointlight ${LINK_LIBRARY})

#pointset example
CONFIGURE_FILE(pointset.cpp.in ${CONF_FILE_DIR}/pointset.cpp)
SET(pointset_SOURCE ${CONF_FILE_DIR}/pointset.cpp)
ADD_EXECUTABLE(pointset ${pointset_SOURCE})
TARGET_LINK_LIBRARIES(pointset ${LINK_LIBRARY})

#quadmesh example
CONFIGURE_FILE(quadmesh.cpp.in ${CONF_FILE_DIR}/quadmesh.cpp)
SET(quadmesh_SOURCE ${CONF_FILE_DIR}/quadmesh.cpp)
ADD_EXECUTABLE(quadmesh ${quadmesh_SOURCE})
TARGET_LINK_LIBRARIES(quadmesh ${LINK_LIBRARY})

#rotation example
CONFIGURE_FILE(rotation.cpp.in ${CONF_FILE_DIR}/rotation.cpp)
SET(rotation_SOURCE ${CONF_FILE_DIR}/rotation.cpp)
ADD_EXECUTABLE(rotation ${rotation_SOURCE})
TARGET_LINK_LIBRARIES(rotation ${LINK_LIBRARY})

#rotor example
CONFIGURE_FILE(rotor.cpp.in ${CONF_FILE_DIR}/rotor.cpp)
SET(rotor_SOURCE ${CONF_FILE_DIR}/rotor.cpp)
ADD_EXECUTABLE(rotor ${rotor_SOURCE})
TARGET_LINK_LIBRARIES(rotor ${LINK_LIBRARY})

#scale example
CONFIGURE_FILE(scale.cpp.in ${CONF_FILE_DIR}/scale.cpp)
SET(scale_SOURCE ${CONF_FILE_DIR}/scale.cpp)
ADD_EXECUTABLE(scale ${scale_SOURCE})
TARGET_LINK_LIBRARIES(scale ${LINK_LIBRARY})

#scenetexture example
CONFIGURE_FILE(scenetexture.cpp.in ${CONF_FILE_DIR}/scenetexture.cpp)
SET(scenetexture_SOURCE ${CONF_FILE_DIR}/scenetexture.cpp)
ADD_EXECUTABLE(scenetexture ${scenetexture_SOURCE})
TARGET_LINK_LIBRARIES(scenetexture ${LINK_LIBRARY})

#selection example
CONFIGURE_FILE(selection.cpp.in ${CONF_FILE_DIR}/selection.cpp)
SET(selection_SOURCE ${CONF_FILE_DIR}/selection.cpp)
ADD_EXECUTABLE(selection ${selection_SOURCE})
TARGET_LINK_LIBRARIES(selection ${LINK_LIBRARY})

#shuttle example
CONFIGURE_FILE(shuttle.cpp.in ${CONF_FILE_DIR}/shuttle.cpp)
SET(shuttle_SOURCE ${CONF_FILE_DIR}/shuttle.cpp)
ADD_EXECUTABLE(shuttle ${shuttle_SOURCE})
TARGET_LINK_LIBRARIES(shuttle ${LINK_LIBRARY})

#slideshow example
CONFIGURE_FILE(slideshow.cpp.in ${CONF_FILE_DIR}/slideshow.cpp)
SET(slideshow_SOURCE ${CONF_FILE_DIR}/slideshow.cpp)
ADD_EXECUTABLE(slideshow ${slideshow_SOURCE})
TARGET_LINK_LIBRARIES(slideshow ${LINK_LIBRARY})

#sphere example
CONFIGURE_FILE(sphere.cpp.in ${CONF_FILE_DIR}/sphere.cpp)
SET(sphere_SOURCE ${CONF_FILE_DIR}/sphere.cpp)
ADD_EXECUTABLE(sphere ${sphere_SOURCE})
TARGET_LINK_LIBRARIES(sphere ${LINK_LIBRARY})

#spherecolor example
CONFIGURE_FILE(spherecolor.cpp.in ${CONF_FILE_DIR}/spherecolor.cpp)
SET(spherecolor_SOURCE ${CONF_FILE_DIR}/spherecolor.cpp)
ADD_EXECUTABLE(spherecolor ${spherecolor_SOURCE})
TARGET_LINK_LIBRARIES(spherecolor ${LINK_LIBRARY})

#spotlight example
CONFIGURE_FILE(spotlight.cpp.in ${CONF_FILE_DIR}/spotlight.cpp)
SET(spotlight_SOURCE ${CONF_FILE_DIR}/spotlight.cpp)
ADD_EXECUTABLE(spotlight ${spotlight_SOURCE})
TARGET_LINK_LIBRARIES(spotlight ${LINK_LIBRARY})

#text2 example
CONFIGURE_FILE(text2.cpp.in ${CONF_FILE_DIR}/text2.cpp)
SET(text2_SOURCE ${CONF_FILE_DIR}/text2.cpp)
ADD_EXECUTABLE(text2 ${text2_SOURCE})
TARGET_LINK_LIBRARIES(text2 ${LINK_LIBRARY})

#text3 example
CONFIGURE_FILE(text3.cpp.in ${CONF_FILE_DIR}/text3.cpp)
SET(text3_SOURCE ${CONF_FILE_DIR}/text3.cpp)
ADD_EXECUTABLE(text3 ${text3_SOURCE})
TARGET_LINK_LIBRARIES(text3 ${LINK_LIBRARY})

#texture example
CONFIGURE_FILE(texture.cpp.in ${CONF_FILE_DIR}/texture.cpp)
SET(texture_SOURCE ${CONF_FILE_DIR}/texture.cpp)
ADD_EXECUTABLE(texture ${texture_SOURCE})
TARGET_LINK_LIBRARIES(texture ${LINK_LIBRARY})

#texture3 example
CONFIGURE_FILE(texture3.cpp.in ${CONF_FILE_DIR}/texture3.cpp)
SET(texture3_SOURCE ${CONF_FILE_DIR}/texture3.cpp)
ADD_EXECUTABLE(texture3 ${texture3_SOURCE})
TARGET_LINK_LIBRARIES(texture3 ${LINK_LIBRARY})

#textureunit example
CONFIGURE_FILE(textureunit.cpp.in ${CONF_FILE_DIR}/textureunit.cpp)
SET(textureunit_SOURCE ${CONF_FILE_DIR}/textureunit.cpp)
ADD_EXECUTABLE(textureunit ${textureunit_SOURCE})
TARGET_LINK_LIBRARIES(textureunit ${LINK_LIBRARY})

#transform example
CONFIGURE_FILE(transform.cpp.in ${CONF_FILE_DIR}/transform.cpp)
SET(transform_SOURCE ${CONF_FILE_DIR}/transform.cpp)
ADD_EXECUTABLE(transform ${transform_SOURCE})
TARGET_LINK_LIBRARIES(transform ${LINK_LIBRARY})

#translation example
CONFIGURE_FILE(translation.cpp.in ${CONF_FILE_DIR}/translation.cpp)
SET(translation_SOURCE ${CONF_FILE_DIR}/translation.cpp)
ADD_EXECUTABLE(translation ${translation_SOURCE})
TARGET_LINK_LIBRARIES(translation ${LINK_LIBRARY})

#trianglestripset example
CONFIGURE_FILE(trianglestripset.cpp.in ${CONF_FILE_DIR}/trianglestripset.cpp)
SET(trianglestripset_SOURCE ${CONF_FILE_DIR}/trianglestripset.cpp)
ADD_EXECUTABLE(trianglestripset ${trianglestripset_SOURCE})
TARGET_LINK_LIBRARIES(trianglestripset ${LINK_LIBRARY})


#Generate the tree structure in the VS Projects.
SIM_VS_GENERATE_BASIC_TREE()

INSTALL(TARGETS atmospheric RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS bigimage RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS blinker RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS bumpmap RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS camera RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS clipplane RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS complexity RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS directionallight RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS drawstyle RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS environment RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS extselection RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS faceset RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS facesetindexed RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS image RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS levelofdetail RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS lights RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS markerset RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS material RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS nurbssurface RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS pointlight RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS pointset RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS quadmesh RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS rotation RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS rotor RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS scale RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS scenetexture RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS selection RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS shuttle RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS slideshow RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS sphere RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS spherecolor RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS spotlight RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS text2 RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS text3 RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS texture RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS texture3 RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS textureunit RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS transform RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS translation RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)

INSTALL(TARGETS trianglestripset RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodes
)