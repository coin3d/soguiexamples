include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#configure files
configure_file(SoGuiSnapshotViewer.h.in SoGuiSnapshotViewer.h)
configure_file(SoGuiSnapshotViewer.cpp.in SoGuiSnapshotViewer.cpp)
configure_file(computils.h.in computils.h)
configure_file(computils.cpp.in computils.cpp)

set(COMPUTILS_SOURCE ${CMAKE_CURRENT_BINARY_DIR}/computils.h ${CMAKE_CURRENT_BINARY_DIR}/computils.cpp)
set(VIEWER_SOURCE ${CMAKE_CURRENT_BINARY_DIR}/SoGuiSnapshotViewer.h ${CMAKE_CURRENT_BINARY_DIR}/SoGuiSnapshotViewer.cpp)

#HAVE_SLIDERSETS found
if(HAVE_SLIDERSETS)
  #lightsliderset example
  configure_file(lightsliderset.cpp.in lightsliderset.cpp)
  add_executable(lightsliderset ${CMAKE_CURRENT_BINARY_DIR}/lightsliderset.cpp)
  target_link_libraries(lightsliderset PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS lightsliderset RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

  #materialsliderset example
  configure_file(materialsliderset.cpp.in materialsliderset.cpp)
  add_executable(materialsliderset ${CMAKE_CURRENT_BINARY_DIR}/materialsliderset.cpp)
  target_link_libraries(materialsliderset PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS materialsliderset RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

  #materialsliderset2 example
  configure_file(materialsliderset2.cpp.in materialsliderset2.cpp)
  add_executable(materialsliderset2 ${CMAKE_CURRENT_BINARY_DIR}/materialsliderset2.cpp)
  target_link_libraries(materialsliderset2 PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS materialsliderset2 RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

  #transformsliderset example
  configure_file(transformsliderset.cpp.in transformsliderset.cpp)
  add_executable(transformsliderset ${CMAKE_CURRENT_BINARY_DIR}/transformsliderset.cpp)
  target_link_libraries(transformsliderset PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS transformsliderset RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

  message(STATUS "Found HAVE_SLIDERSETS")
endif()

#HAVE_SLIDERSETS found
if(HAVE_MATERIALEDITOR)
  #materialeditor example
  configure_file(materialeditor.cpp.in materialeditor.cpp)
  add_executable(materialeditor ${CMAKE_CURRENT_BINARY_DIR}/materialeditor.cpp)
  target_link_libraries(materialeditor PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS materialeditor RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)
  message(STATUS "Found HAVE_SLIDERSETS")
endif()

#HAVE_MATERIALLIST found
if(HAVE_MATERIALLIST)
  #materiallist example
  configure_file(materiallist.cpp.in materiallist.cpp)
  add_executable(materiallist ${CMAKE_CURRENT_BINARY_DIR}/materiallist.cpp)
  target_link_libraries(materiallist PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS materiallist RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

  #materiallist2 example
  configure_file(materiallist2.cpp.in materiallist2.cpp)
  add_executable(materiallist2 ${CMAKE_CURRENT_BINARY_DIR}/materiallist2.cpp)
  target_link_libraries(materiallist2 PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS materiallist2 RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

  message(STATUS "Found HAVE_MATERIALLIST")
endif()

#HAVE_PRINTDIALOG Found
if(HAVE_PRINTDIALOG)
  #printdialog example
  configure_file(printdialog.cpp.in printdialog.cpp)
  add_executable(printdialog ${CMAKE_CURRENT_BINARY_DIR}/printdialog.cpp)
  target_link_libraries(printdialog PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS printdialog RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)
  message(STATUS "Found HAVE_PRINTDIALOG")
endif()

#HAVE_ROSTER Found
if(HAVE_ROSTER)
  #roster example
  configure_file(roster.cpp.in roster.cpp)
  add_executable(roster ${CMAKE_CURRENT_BINARY_DIR}/roster.cpp)
  target_link_libraries(roster PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS roster RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)
  message(STATUS "Found HAVE_ROSTER")
endif()

#HAVE_DIRECTIONALLIGHTEDITOR Found
if(HAVE_DIRECTIONALLIGHTEDITOR)
  #directionallighteditor example
  configure_file(directionallighteditor.cpp.in directionallighteditor.cpp)
  add_executable(directionallighteditor ${CMAKE_CURRENT_BINARY_DIR}/directionallighteditor.cpp)
  target_link_libraries(directionallighteditor PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS directionallighteditor RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)
  message(STATUS "HAVE_DIRECTIONALLIGHTEDITOR Found")
endif()

#backgroundimg example
configure_file(backgroundimg.cpp.in backgroundimg.cpp)
add_executable(backgroundimg ${CMAKE_CURRENT_BINARY_DIR}/backgroundimg.cpp)
target_link_libraries(backgroundimg PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES} ${OPENGL_LIBRARIES})
install(TARGETS backgroundimg RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

#examinerviewer example
configure_file(examinerviewer.cpp.in examinerviewer.cpp)
add_executable(examinerviewer ${CMAKE_CURRENT_BINARY_DIR}/examinerviewer.cpp ${COMPUTILS_SOURCE})
target_link_libraries(examinerviewer PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS examinerviewer RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

#flyviewer example
configure_file(flyviewer.cpp.in flyviewer.cpp)
add_executable(flyviewer ${CMAKE_CURRENT_BINARY_DIR}/flyviewer.cpp ${COMPUTILS_SOURCE})
target_link_libraries(flyviewer PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS flyviewer RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

#grapheditor example
#configure_file(grapheditor.cpp.in grapheditor.cpp)
#add_executable(grapheditor ${CMAKE_CURRENT_BINARY_DIR}/grapheditor.cpp ${COMPUTILS_SOURCE})
#target_link_libraries(grapheditor PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
#install(TARGETS grapheditor RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

#multifileviewer example
configure_file(multifileviewer.cpp.in multifileviewer.cpp)
add_executable(multifileviewer ${CMAKE_CURRENT_BINARY_DIR}/multifileviewer.cpp)
target_link_libraries(multifileviewer PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS multifileviewer RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

#overlay example
configure_file(overlay.cpp.in overlay.cpp)
add_executable(overlay ${CMAKE_CURRENT_BINARY_DIR}/overlay.cpp ${COMPUTILS_SOURCE})
target_link_libraries(overlay PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS overlay RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

#planeviewer example
configure_file(planeviewer.cpp.in planeviewer.cpp)
add_executable(planeviewer ${CMAKE_CURRENT_BINARY_DIR}/planeviewer.cpp ${COMPUTILS_SOURCE})
target_link_libraries(planeviewer PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS planeviewer RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

#renderarea example
configure_file(renderarea.cpp.in renderarea.cpp)
add_executable(renderarea ${CMAKE_CURRENT_BINARY_DIR}/renderarea.cpp ${COMPUTILS_SOURCE})
target_link_libraries(renderarea PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS renderarea RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

#simpleexviewer example
configure_file(simpleexviewer.cpp.in simpleexviewer.cpp)
add_executable(simpleexviewer ${CMAKE_CURRENT_BINARY_DIR}/simpleexviewer.cpp)
target_link_libraries(simpleexviewer PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS simpleexviewer RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

#simplerenderarea example
configure_file(simplerenderarea.cpp.in simplerenderarea.cpp)
add_executable(simplerenderarea ${CMAKE_CURRENT_BINARY_DIR}/simplerenderarea.cpp)
target_link_libraries(simplerenderarea PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS simplerenderarea RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

#snapshotviewer example
configure_file(snapshotviewer.cpp.in snapshotviewer.cpp)
add_executable(snapshotviewer ${CMAKE_CURRENT_BINARY_DIR}/snapshotviewer.cpp ${COMPUTILS_SOURCE} ${VIEWER_SOURCE})
target_link_libraries(snapshotviewer PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS snapshotviewer RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

#subfullviewer example
configure_file(subfullviewer.cpp.in subfullviewer.cpp)
add_executable(subfullviewer ${CMAKE_CURRENT_BINARY_DIR}/subfullviewer.cpp)
target_link_libraries(subfullviewer PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS subfullviewer RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

#subviewer example
configure_file(subviewer.cpp.in subviewer.cpp)
add_executable(subviewer ${CMAKE_CURRENT_BINARY_DIR}/subviewer.cpp)
target_link_libraries(subviewer PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS subviewer RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)

#walkviewer example
#configure_file(walkviewer.cpp.in walkviewer.cpp)
#add_executable(walkviewer ${CMAKE_CURRENT_BINARY_DIR}/walkviewer.cpp ${COMPUTILS_SOURCE})
#target_link_libraries(walkviewer PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
#install(TARGETS walkviewer RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/components)
