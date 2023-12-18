if(Qt6_FOUND OR Qt5_FOUND OR Qt4_FOUND)
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTOUIC ON)

  set(CMAKE_INCLUDE_CURRENT_DIR ON)

  add_subdirectory(Cute)

  list(APPEND SOGUIEXAMPLES_LINK_LIBRARIES CUTE)

  #Transfer
  set(Transfer_SOURCES TransferFunctionHandler.cpp)
  set(Transfer_HEADERS TransferFunctionHandler.h)
  set(Transfer_FORMS SoTransferFunction.ui)

  #OrthoSlice
  set(OrthoSlice_SOURCES OrthoSliceHandler.cpp)
  set(OrthoSlice_HEADERS OrthoSliceHandler.h)
  set(OrthoSlice_FORMS SoOrthoSlice.ui)

  #Volume
  set(Volume_SOURCES VolumeRenderHandler.cpp)
  set(Volume_HEADERS VolumeRenderHandler.h)
  set(Volume_FORMS SoVolumeRender.ui)

  #readvol example
  configure_file(readvol.cpp.in readvol.cpp)
  #add_executable(readvol ${CMAKE_CURRENT_BINARY_DIR}/readvol.cpp ${Transfer_SOURCES} ${Transfer_HEADERS_MOC} ${Transfer_FORMS_HEADERS} ${Volume_SOURCES} ${Volume_HEADERS_MOC} ${Volume_FORMS_HEADERS})
  add_executable(readvol ${CMAKE_CURRENT_BINARY_DIR}/readvol.cpp ${Transfer_SOURCES} ${Transfer_HEADERS} ${Transfer_FORMS} ${Volume_SOURCES} ${Volume_HEADERS} ${Volume_FORMS})
  target_link_libraries(readvol PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS readvol RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/volumerendering)

  #orthoslicer example
  configure_file(orthoslicer.cpp.in orthoslicer.cpp)
  #add_executable(orthoslicer ${CMAKE_CURRENT_BINARY_DIR}/orthoslicer.cpp utility.cpp utility.h ${Transfer_SOURCES} ${Transfer_HEADERS_MOC} ${Transfer_FORMS_HEADERS} ${OrthoSlice_SOURCES} ${OrthoSlice_HEADERS_MOC} ${OrthoSlice_FORMS_HEADERS})
  add_executable(orthoslicer ${CMAKE_CURRENT_BINARY_DIR}/orthoslicer.cpp utility.cpp utility.h ${Transfer_SOURCES} ${Transfer_HEADERS} ${Transfer_FORMS} ${OrthoSlice_SOURCES} ${OrthoSlice_HEADERS} ${OrthoSlice_FORMS})
  target_link_libraries(orthoslicer PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS orthoslicer RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/volumerendering)

  #changingdataset example
  configure_file(changingdataset.cpp.in changingdataset.cpp)
  add_executable(changingdataset ${CMAKE_CURRENT_BINARY_DIR}/changingdataset.cpp)
  target_link_libraries(changingdataset PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS changingdataset RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/volumerendering)

  #examine example
  configure_file(examine.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/examine.cpp)
  add_executable(examine ${CMAKE_CURRENT_BINARY_DIR}/examine.cpp utility.cpp utility.h)
  target_link_libraries(examine PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS examine RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/volumerendering)

  #raypick_volum example
  configure_file(raypick.cpp.in raypick.cpp)
  add_executable(raypick_volum ${CMAKE_CURRENT_BINARY_DIR}/raypick.cpp utility.cpp utility.h)
  target_link_libraries(raypick_volum PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS raypick_volum RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/volumerendering)

  #simple8bit example
  configure_file(simple8bit.cpp.in simple8bit.cpp)
  add_executable(simple8bit ${CMAKE_CURRENT_BINARY_DIR}/simple8bit.cpp utility.cpp utility.h)
  target_link_libraries(simple8bit PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS simple8bit RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/volumerendering)

  #opaquechair example
  add_executable(opaquechair chair.cpp OpaqueChair.cpp OpaqueChair.h OpaqueChair-iv.h)
  target_link_libraries(opaquechair PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS opaquechair RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/volumerendering)

  #voleonexplore example
  configure_file(voleonexplore.cpp voleonexplore.cpp)
  add_executable(voleonexplore ${CMAKE_CURRENT_BINARY_DIR}/voleonexplore.cpp)
  target_link_libraries(voleonexplore PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS voleonexplore RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/volumerendering)

  #fencediagram example
  configure_file(fencediagram.cpp fencediagram.cpp)
  add_executable(fencediagram ${CMAKE_CURRENT_BINARY_DIR}/fencediagram.cpp)
  target_link_libraries(fencediagram PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS fencediagram RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/volumerendering)

  #copy the .iv file(s) to build directory
  file(COPY OpaqueChair.iv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

  #copy files to install directory
  install(FILES OpaqueChair.iv DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/volumerendering)
endif()
