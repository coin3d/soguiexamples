include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#atmospheric example
configure_file(atmospheric.cpp.in atmospheric.cpp)
add_executable(atmospheric ${CMAKE_CURRENT_BINARY_DIR}/atmospheric.cpp)
target_link_libraries(atmospheric PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS atmospheric RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#bigimage example
configure_file(bigimage.cpp.in bigimage.cpp)
add_executable(bigimage ${CMAKE_CURRENT_BINARY_DIR}/bigimage.cpp)
target_link_libraries(bigimage PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS bigimage RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#blinker example
configure_file(blinker.cpp.in blinker.cpp)
add_executable(blinker ${CMAKE_CURRENT_BINARY_DIR}/blinker.cpp)
target_link_libraries(blinker PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS blinker RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#bumpmap example
configure_file(bumpmap.cpp.in bumpmap.cpp)
add_executable(bumpmap ${CMAKE_CURRENT_BINARY_DIR}/bumpmap.cpp )
target_link_libraries(bumpmap PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS bumpmap RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#camera example
configure_file(camera.cpp.in camera.cpp)
add_executable(camera ${CMAKE_CURRENT_BINARY_DIR}/camera.cpp)
target_link_libraries(camera PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS camera RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#clipplane example
configure_file(clipplane.cpp.in clipplane.cpp)
add_executable(clipplane ${CMAKE_CURRENT_BINARY_DIR}/clipplane.cpp)
target_link_libraries(clipplane PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS clipplane RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#complexity example
configure_file(complexity.cpp.in complexity.cpp)
add_executable(complexity ${CMAKE_CURRENT_BINARY_DIR}/complexity.cpp)
target_link_libraries(complexity PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS complexity RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#directionallight example
configure_file(directionallight.cpp.in directionallight.cpp)
add_executable(directionallight ${CMAKE_CURRENT_BINARY_DIR}/directionallight.cpp)
target_link_libraries(directionallight PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS directionallight RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#drawstyle example
configure_file(drawstyle.cpp.in drawstyle.cpp)
add_executable(drawstyle ${CMAKE_CURRENT_BINARY_DIR}/drawstyle.cpp)
target_link_libraries(drawstyle PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS drawstyle RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#environment example
configure_file(environment.cpp.in environment.cpp)
add_executable(environment ${CMAKE_CURRENT_BINARY_DIR}/environment.cpp)
target_link_libraries(environment PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS environment RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#extselection example
configure_file(extselection.cpp.in extselection.cpp)
add_executable(extselection ${CMAKE_CURRENT_BINARY_DIR}/extselection.cpp)
target_link_libraries(extselection PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS extselection RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#faceset example
configure_file(faceset.cpp.in faceset.cpp)
add_executable(faceset ${CMAKE_CURRENT_BINARY_DIR}/faceset.cpp)
target_link_libraries(faceset PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS faceset RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#facesetindexed example
configure_file(facesetindexed.cpp.in facesetindexed.cpp)
add_executable(facesetindexed ${CMAKE_CURRENT_BINARY_DIR}/facesetindexed.cpp)
target_link_libraries(facesetindexed PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS facesetindexed RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#image example
configure_file(image.cpp.in image.cpp)
add_executable(image ${CMAKE_CURRENT_BINARY_DIR}/image.cpp)
target_link_libraries(image PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS image RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#levelofdetail example
configure_file(levelofdetail.cpp.in levelofdetail.cpp)
add_executable(levelofdetail ${CMAKE_CURRENT_BINARY_DIR}/levelofdetail.cpp)
target_link_libraries(levelofdetail PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS levelofdetail RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#lights example
configure_file(lights.cpp.in lights.cpp)
add_executable(lights ${CMAKE_CURRENT_BINARY_DIR}/lights.cpp)
target_link_libraries(lights PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS lights RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#markerset example
configure_file(markerset.cpp.in markerset.cpp)
add_executable(markerset ${CMAKE_CURRENT_BINARY_DIR}/markerset.cpp)
target_link_libraries(markerset PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS markerset RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#material example
configure_file(material.cpp.in material.cpp)
add_executable(material ${CMAKE_CURRENT_BINARY_DIR}/material.cpp)
target_link_libraries(material PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS material RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#nurbssurface example
configure_file(nurbssurface.cpp.in nurbssurface.cpp)
add_executable(nurbssurface ${CMAKE_CURRENT_BINARY_DIR}/nurbssurface.cpp)
target_link_libraries(nurbssurface PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS nurbssurface RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#pointlight example
configure_file(pointlight.cpp.in pointlight.cpp)
add_executable(pointlight ${CMAKE_CURRENT_BINARY_DIR}/pointlight.cpp)
target_link_libraries(pointlight PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS pointlight RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#pointset example
configure_file(pointset.cpp.in pointset.cpp)
add_executable(pointset ${CMAKE_CURRENT_BINARY_DIR}/pointset.cpp)
target_link_libraries(pointset PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS pointset RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#quadmesh example
configure_file(quadmesh.cpp.in quadmesh.cpp)
add_executable(quadmesh ${CMAKE_CURRENT_BINARY_DIR}/quadmesh.cpp)
target_link_libraries(quadmesh PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS quadmesh RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#rotation example
configure_file(rotation.cpp.in rotation.cpp)
add_executable(rotation ${CMAKE_CURRENT_BINARY_DIR}/rotation.cpp)
target_link_libraries(rotation PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS rotation RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#rotor example
configure_file(rotor.cpp.in rotor.cpp)
add_executable(rotor ${CMAKE_CURRENT_BINARY_DIR}/rotor.cpp)
target_link_libraries(rotor PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS rotor RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#scale example
configure_file(scale.cpp.in scale.cpp)
add_executable(scale ${CMAKE_CURRENT_BINARY_DIR}/scale.cpp)
target_link_libraries(scale PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS scale RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#scenetexture example
configure_file(scenetexture.cpp.in scenetexture.cpp)
add_executable(scenetexture ${CMAKE_CURRENT_BINARY_DIR}/scenetexture.cpp)
target_link_libraries(scenetexture PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS scenetexture RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#selection example
configure_file(selection.cpp.in selection.cpp)
add_executable(selection ${CMAKE_CURRENT_BINARY_DIR}/selection.cpp)
target_link_libraries(selection PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS selection RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#shuttle example
configure_file(shuttle.cpp.in shuttle.cpp)
add_executable(shuttle ${CMAKE_CURRENT_BINARY_DIR}/shuttle.cpp)
target_link_libraries(shuttle PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS shuttle RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#slideshow example
configure_file(slideshow.cpp.in slideshow.cpp)
add_executable(slideshow ${CMAKE_CURRENT_BINARY_DIR}/slideshow.cpp)
target_link_libraries(slideshow PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS slideshow RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#sphere example
configure_file(sphere.cpp.in sphere.cpp)
add_executable(sphere ${CMAKE_CURRENT_BINARY_DIR}/sphere.cpp)
target_link_libraries(sphere PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS sphere RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#spherecolor example
configure_file(spherecolor.cpp.in spherecolor.cpp)
add_executable(spherecolor ${CMAKE_CURRENT_BINARY_DIR}/spherecolor.cpp)
target_link_libraries(spherecolor PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS spherecolor RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#spotlight example
configure_file(spotlight.cpp.in spotlight.cpp)
add_executable(spotlight ${CMAKE_CURRENT_BINARY_DIR}/spotlight.cpp)
target_link_libraries(spotlight PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS spotlight RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#text2 example
configure_file(text2.cpp.in text2.cpp)
add_executable(text2 ${CMAKE_CURRENT_BINARY_DIR}/text2.cpp)
target_link_libraries(text2 PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS text2 RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#text3 example
configure_file(text3.cpp.in text3.cpp)
add_executable(text3 ${CMAKE_CURRENT_BINARY_DIR}/text3.cpp)
target_link_libraries(text3 PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS text3 RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#texture example
configure_file(texture.cpp.in texture.cpp)
add_executable(texture ${CMAKE_CURRENT_BINARY_DIR}/texture.cpp)
target_link_libraries(texture PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS texture RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#texture3 example
configure_file(texture3.cpp.in texture3.cpp)
add_executable(texture3 ${CMAKE_CURRENT_BINARY_DIR}/texture3.cpp)
target_link_libraries(texture3 PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS texture3 RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#textureunit example
configure_file(textureunit.cpp.in textureunit.cpp)
add_executable(textureunit ${CMAKE_CURRENT_BINARY_DIR}/textureunit.cpp)
target_link_libraries(textureunit PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS textureunit RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#transform example
configure_file(transform.cpp.in transform.cpp)
add_executable(transform ${CMAKE_CURRENT_BINARY_DIR}/transform.cpp)
target_link_libraries(transform PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS transform RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#translation example
configure_file(translation.cpp.in translation.cpp)
add_executable(translation ${CMAKE_CURRENT_BINARY_DIR}/translation.cpp)
target_link_libraries(translation PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS translation RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)

#trianglestripset example
configure_file(trianglestripset.cpp.in trianglestripset.cpp)
add_executable(trianglestripset ${CMAKE_CURRENT_BINARY_DIR}/trianglestripset.cpp)
target_link_libraries(trianglestripset PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS trianglestripset RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodes)
