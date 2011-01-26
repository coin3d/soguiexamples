SET(UI_HEADER_DIR uiheader)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR}/${UI_HEADER_DIR})

IF(HAVE_QT3SUPPORT_LIBRARY)

INCLUDE_DIRECTORIES(${QT_INCLUDE_DIR}/Qt3Support)

SET(LINK_LIBRARY ${Coin_LIBRARY} ${SmallChange_LIBRARY} ${SoQt_LIBRARY} ${QT_LIBRARIES} ${QT_QT3SUPPORT_LIBRARY} ${SIMVoleon_LIBRARY})

INCLUDE_DIRECTORIES(./)
SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/volumerendering)
INCLUDE_DIRECTORIES(${CONF_FILE_DIR})

ADD_SUBDIRECTORY(Cute)

LINK_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
SET(LINK_LIBRARY ${LINK_LIBRARY} CUTE)

#Transfer
SET(Transfer_SOURCES TransferFunctionHandler.cpp)
SET(Transfer_HEADERS TransferFunctionHandler.h)
SET(Transfer_FORMS SoTransferFunction_ctrl.ui)
#QT4_WRAP_CPP(Transfer_HEADERS_MOC ${Transfer_HEADERS})
#QT4_WRAP_UI(Transfer_FORMS_HEADERS ${Transfer_FORMS})
SIM_QT4_AUTO_WRAP_CPP(Transfer_HEADERS_MOC ${Transfer_HEADERS})
SIM_QT4_WRAP_UI_TO(Transfer_FORMS_HEADERS ${UI_HEADER_DIR} ${Transfer_FORMS})

#OrthoSlice
SET(OrthoSlice_SOURCES OrthoSliceHandler.cpp)
SET(OrthoSlice_HEADERS OrthoSliceHandler.h)
SET(OrthoSlice_FORMS SoOrthoSlice_ctrl.ui)
#QT4_WRAP_CPP(OrthoSlice_HEADERS_MOC ${OrthoSlice_HEADERS})
#QT4_WRAP_UI(OrthoSlice_FORMS_HEADERS ${OrthoSlice_FORMS})
SIM_QT4_AUTO_WRAP_CPP(OrthoSlice_HEADERS_MOC ${OrthoSlice_HEADERS})
SIM_QT4_WRAP_UI_TO(OrthoSlice_FORMS_HEADERS ${UI_HEADER_DIR} ${OrthoSlice_FORMS})

#Volume
SET(Volume_SOURCES VolumeRenderHandler.cpp)
SET(Volume_HEADERS VolumeRenderHandler.h)
SET(Volume_FORMS SoVolumeRender_ctrl.ui)
#QT4_WRAP_CPP(Volume_HEADERS_MOC ${Volume_HEADERS})
#QT4_WRAP_UI(Volume_FORMS_HEADERS ${Volume_FORMS})
SIM_QT4_AUTO_WRAP_CPP(Volume_HEADERS_MOC ${Volume_HEADERS})
SIM_QT4_WRAP_UI_TO(Volume_FORMS_HEADERS ${UI_HEADER_DIR} ${Volume_FORMS})


#readvol example
CONFIGURE_FILE(readvol.cpp.in ${CONF_FILE_DIR}/readvol.cpp)

SET(readvol_SOURCE ${CONF_FILE_DIR}/readvol.cpp  ${Transfer_SOURCES} ${Transfer_HEADERS_MOC} ${Transfer_FORMS_HEADERS} ${Volume_SOURCES} ${Volume_HEADERS_MOC} ${Volume_FORMS_HEADERS})

ADD_EXECUTABLE(readvol ${readvol_SOURCE})
TARGET_LINK_LIBRARIES(readvol ${LINK_LIBRARY})


#orthoslicer example
CONFIGURE_FILE(orthoslicer.cpp.in ${CONF_FILE_DIR}/orthoslicer.cpp)

SET(orthoslicer_SOURCE ${CONF_FILE_DIR}/orthoslicer.cpp  utility.cpp utility.h ${Transfer_SOURCES} ${Transfer_HEADERS_MOC} ${Transfer_FORMS_HEADERS} ${OrthoSlice_SOURCES} ${OrthoSlice_HEADERS_MOC} ${OrthoSlice_FORMS_HEADERS})

ADD_EXECUTABLE(orthoslicer ${orthoslicer_SOURCE})
TARGET_LINK_LIBRARIES(orthoslicer ${LINK_LIBRARY})


#changingdataset example
CONFIGURE_FILE(changingdataset.cpp.in ${CONF_FILE_DIR}/changingdataset.cpp)

SET(changingdataset_SOURCE ${CONF_FILE_DIR}/changingdataset.cpp)

ADD_EXECUTABLE(changingdataset ${changingdataset_SOURCE})
TARGET_LINK_LIBRARIES(changingdataset ${LINK_LIBRARY})


#examine example
CONFIGURE_FILE(examine.cpp.in ${CONF_FILE_DIR}/examine.cpp)

SET(examine_SOURCE ${CONF_FILE_DIR}/examine.cpp  utility.cpp utility.h)

ADD_EXECUTABLE(examine ${examine_SOURCE})
TARGET_LINK_LIBRARIES(examine ${LINK_LIBRARY})


#raypick_volum example
CONFIGURE_FILE(raypick.cpp.in ${CONF_FILE_DIR}/raypick.cpp)

SET(raypick_SOURCE ${CONF_FILE_DIR}/raypick.cpp  utility.cpp utility.h)

ADD_EXECUTABLE(raypick_volum ${raypick_SOURCE})
TARGET_LINK_LIBRARIES(raypick_volum ${LINK_LIBRARY})


#simple8bit example
CONFIGURE_FILE(simple8bit.cpp.in ${CONF_FILE_DIR}/simple8bit.cpp)

SET(simple8bit_SOURCE ${CONF_FILE_DIR}/simple8bit.cpp  utility.cpp utility.h)

ADD_EXECUTABLE(simple8bit ${simple8bit_SOURCE})
TARGET_LINK_LIBRARIES(simple8bit ${LINK_LIBRARY})


#opaquechair example
SET(opaquechair_SOURCE chair.cpp OpaqueChair.cpp OpaqueChair.h OpaqueChair-iv.h)

ADD_EXECUTABLE(opaquechair ${opaquechair_SOURCE})
TARGET_LINK_LIBRARIES(opaquechair ${LINK_LIBRARY})


#voleonexplore example
CONFIGURE_FILE(voleonexplore.cpp ${CONF_FILE_DIR}/voleonexplore.cpp)

SET(voleonexplore_SOURCE ${CONF_FILE_DIR}/voleonexplore.cpp)

ADD_EXECUTABLE(voleonexplore ${voleonexplore_SOURCE})
TARGET_LINK_LIBRARIES(voleonexplore ${LINK_LIBRARY})


#fencediagram example
CONFIGURE_FILE(fencediagram.cpp ${CONF_FILE_DIR}/fencediagram.cpp)

SET(fencediagram_SOURCE ${CONF_FILE_DIR}/fencediagram.cpp)

ADD_EXECUTABLE(fencediagram ${fencediagram_SOURCE})
TARGET_LINK_LIBRARIES(fencediagram ${LINK_LIBRARY})


# copy over the .iv file
CONFIGURE_FILE(OpaqueChair.iv ${CONF_FILE_DIR}/volumerendering/OpaqueChair.iv COPYONLY)


#Generate the tree structure in the VS Projects.
SIM_VS_GENERATE_BASIC_TREE()

INSTALL(TARGETS readvol
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/volumerendering
)
INSTALL(TARGETS orthoslicer
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/volumerendering
)
INSTALL(TARGETS changingdataset
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/volumerendering
)
INSTALL(TARGETS examine
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/volumerendering
)
INSTALL(TARGETS raypick_volum
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/volumerendering
)
INSTALL(TARGETS simple8bit
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/volumerendering
)

INSTALL(TARGETS opaquechair
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/volumerendering
)

INSTALL(TARGETS voleonexplore
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/volumerendering
)
INSTALL(TARGETS fencediagram
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/volumerendering
)

#copy the OpaqueChair.iv to build directory
INSTALL(DIRECTORY ./ DESTINATION ${CURRENT_BUILD_DIR}/volumerendering
        FILES_MATCHING PATTERN "*.iv"
        PATTERN ".hg" EXCLUDE)

ENDIF(HAVE_QT3SUPPORT_LIBRARY)
