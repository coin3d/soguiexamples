INCLUDE_DIRECTORIES(./)
SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/components)
INCLUDE_DIRECTORIES(${CONF_FILE_DIR})

#configure files
CONFIGURE_FILE(SoGuiSnapshotViewer.h.in ${CONF_FILE_DIR}/SoGuiSnapshotViewer.h)
CONFIGURE_FILE(SoGuiSnapshotViewer.cpp.in ${CONF_FILE_DIR}/SoGuiSnapshotViewer.cpp)
CONFIGURE_FILE(backgroundimg.cpp.in ${CONF_FILE_DIR}/backgroundimg.cpp)
CONFIGURE_FILE(computils.h.in ${CONF_FILE_DIR}/computils.h)
CONFIGURE_FILE(computils.cpp.in ${CONF_FILE_DIR}/computils.cpp)
CONFIGURE_FILE(directionallighteditor.cpp.in ${CONF_FILE_DIR}/directionallighteditor.cpp)
CONFIGURE_FILE(examinerviewer.cpp.in ${CONF_FILE_DIR}/examinerviewer.cpp)
CONFIGURE_FILE(flyviewer.cpp.in ${CONF_FILE_DIR}/flyviewer.cpp)
CONFIGURE_FILE(grapheditor.cpp.in ${CONF_FILE_DIR}/grapheditor.cpp)
CONFIGURE_FILE(lightsliderset.cpp.in ${CONF_FILE_DIR}/lightsliderset.cpp)
CONFIGURE_FILE(materialeditor.cpp.in ${CONF_FILE_DIR}/materialeditor.cpp)
CONFIGURE_FILE(materiallist.cpp.in ${CONF_FILE_DIR}/materiallist.cpp)
CONFIGURE_FILE(materiallist2.cpp.in ${CONF_FILE_DIR}/materiallist2.cpp)
CONFIGURE_FILE(materialsliderset.cpp.in ${CONF_FILE_DIR}/materialsliderset.cpp)
CONFIGURE_FILE(materialsliderset2.cpp.in ${CONF_FILE_DIR}/materialsliderset2.cpp)
CONFIGURE_FILE(multifileviewer.cpp.in ${CONF_FILE_DIR}/multifileviewer.cpp)
CONFIGURE_FILE(overlay.cpp.in ${CONF_FILE_DIR}/overlay.cpp)
CONFIGURE_FILE(planeviewer.cpp.in ${CONF_FILE_DIR}/planeviewer.cpp)
CONFIGURE_FILE(printdialog.cpp.in ${CONF_FILE_DIR}/printdialog.cpp)
CONFIGURE_FILE(renderarea.cpp.in ${CONF_FILE_DIR}/renderarea.cpp)
CONFIGURE_FILE(roster.cpp.in ${CONF_FILE_DIR}/roster.cpp)
CONFIGURE_FILE(simpleexviewer.cpp.in ${CONF_FILE_DIR}/simpleexviewer.cpp)
CONFIGURE_FILE(simplerenderarea.cpp.in ${CONF_FILE_DIR}/simplerenderarea.cpp)
CONFIGURE_FILE(snapshotviewer.cpp.in ${CONF_FILE_DIR}/snapshotviewer.cpp)
CONFIGURE_FILE(subfullviewer.cpp.in ${CONF_FILE_DIR}/subfullviewer.cpp)
CONFIGURE_FILE(subviewer.cpp.in ${CONF_FILE_DIR}/subviewer.cpp)
CONFIGURE_FILE(transformsliderset.cpp.in ${CONF_FILE_DIR}/transformsliderset.cpp)
#CONFIGURE_FILE(walkviewer.cpp.in ${CONF_FILE_DIR}/walkviewer.cpp)
CONFIGURE_FILE(computils.h.in ${CONF_FILE_DIR}/computils.h)

SET(COMPUTILS_SOURCE ${CONF_FILE_DIR}/computils.h ${CONF_FILE_DIR}/computils.cpp)
SET(VIEWER_SOURCE ${CONF_FILE_DIR}/SoGuiSnapshotViewer.h ${CONF_FILE_DIR}/SoGuiSnapshotViewer.cpp)

#HAVE_SLIDERSETS found
IF(HAVE_SLIDERSETS)
#lightsliderset example
SET(lightsliderset_SOURCE ${CONF_FILE_DIR}/lightsliderset.cpp)
ADD_EXECUTABLE(lightsliderset ${lightsliderset_SOURCE})
TARGET_LINK_LIBRARIES(lightsliderset ${LINK_LIBRARY})

#materialsliderset example
SET(materialsliderset_SOURCE ${CONF_FILE_DIR}/materialsliderset.cpp)
ADD_EXECUTABLE(materialsliderset ${materialsliderset_SOURCE})
TARGET_LINK_LIBRARIES(materialsliderset ${LINK_LIBRARY})

#materialsliderset2 example
SET(materialsliderset2_SOURCE ${CONF_FILE_DIR}/materialsliderset2.cpp)
ADD_EXECUTABLE(materialsliderset2 ${materialsliderset2_SOURCE})
TARGET_LINK_LIBRARIES(materialsliderset2 ${LINK_LIBRARY})

#transformsliderset example
SET(transformsliderset_SOURCE ${CONF_FILE_DIR}/transformsliderset.cpp)
ADD_EXECUTABLE(transformsliderset ${transformsliderset_SOURCE})
TARGET_LINK_LIBRARIES(transformsliderset ${LINK_LIBRARY})

MESSAGE(STATUS "Found HAVE_SLIDERSETS")
ENDIF(HAVE_SLIDERSETS)

#HAVE_SLIDERSETS found
IF(HAVE_MATERIALEDITOR)
#materialeditor example
SET(materialeditor_SOURCE ${CONF_FILE_DIR}/materialeditor.cpp)
ADD_EXECUTABLE(materialeditor ${materialeditor_SOURCE})
TARGET_LINK_LIBRARIES(materialeditor ${LINK_LIBRARY})

MESSAGE(STATUS "Found HAVE_SLIDERSETS")
ENDIF(HAVE_MATERIALEDITOR)

#HAVE_MATERIALLIST found
IF(HAVE_MATERIALLIST)
#materiallist example
SET(materiallist_SOURCE ${CONF_FILE_DIR}/materiallist.cpp)
ADD_EXECUTABLE(materiallist ${materiallist_SOURCE})
TARGET_LINK_LIBRARIES(materiallist ${LINK_LIBRARY})

#materiallist2 example
SET(materiallist2_SOURCE ${CONF_FILE_DIR}/materiallist2.cpp)
ADD_EXECUTABLE(materiallist2 ${materiallist2_SOURCE})
TARGET_LINK_LIBRARIES(materiallist2 ${LINK_LIBRARY})

MESSAGE(STATUS "Found HAVE_MATERIALLIST")
ENDIF(HAVE_MATERIALLIST)

#HAVE_PRINTDIALOG Found
IF(HAVE_PRINTDIALOG)
#printdialog example
SET(printdialog_SOURCE ${CONF_FILE_DIR}/printdialog.cpp)
ADD_EXECUTABLE(printdialog ${printdialog_SOURCE})
TARGET_LINK_LIBRARIES(printdialog ${LINK_LIBRARY})

MESSAGE(STATUS "Found HAVE_PRINTDIALOG")
ENDIF(HAVE_PRINTDIALOG)

#HAVE_ROSTER Found
IF(HAVE_ROSTER)
#roster example
SET(roster_SOURCE ${CONF_FILE_DIR}/roster.cpp)
ADD_EXECUTABLE(roster ${roster_SOURCE})
TARGET_LINK_LIBRARIES(roster ${LINK_LIBRARY})

MESSAGE(STATUS "Found HAVE_ROSTER")
ENDIF(HAVE_ROSTER)

#HAVE_DIRECTIONALLIGHTEDITOR Found
IF(HAVE_DIRECTIONALLIGHTEDITOR)
#directionallighteditor example
SET(directionallighteditor_SOURCE ${CONF_FILE_DIR}/directionallighteditor.cpp)
ADD_EXECUTABLE(directionallighteditor ${directionallighteditor_SOURCE})
TARGET_LINK_LIBRARIES(directionallighteditor ${LINK_LIBRARY})

MESSAGE(STATUS "HAVE_DIRECTIONALLIGHTEDITOR Found")
ENDIF(HAVE_DIRECTIONALLIGHTEDITOR)

#backgroundimg example
SET(backgroundimg_SOURCE ${CONF_FILE_DIR}/backgroundimg.cpp)
ADD_EXECUTABLE(backgroundimg ${backgroundimg_SOURCE})
TARGET_LINK_LIBRARIES(backgroundimg ${LINK_LIBRARY})

#examinerviewer example
SET(examinerviewer_SOURCE ${CONF_FILE_DIR}/examinerviewer.cpp ${COMPUTILS_SOURCE})
ADD_EXECUTABLE(examinerviewer ${examinerviewer_SOURCE})
TARGET_LINK_LIBRARIES(examinerviewer ${LINK_LIBRARY})

#flyviewer example
SET(flyviewer_SOURCE ${CONF_FILE_DIR}/flyviewer.cpp ${COMPUTILS_SOURCE})
ADD_EXECUTABLE(flyviewer ${flyviewer_SOURCE})
TARGET_LINK_LIBRARIES(flyviewer ${LINK_LIBRARY})

#grapheditor example
#SET(grapheditor_SOURCE ${CONF_FILE_DIR}/grapheditor.cpp ${COMPUTILS_SOURCE})
#ADD_EXECUTABLE(grapheditor ${grapheditor_SOURCE})
#TARGET_LINK_LIBRARIES(grapheditor ${LINK_LIBRARY})

#multifileviewer example
SET(multifileviewer_SOURCE ${CONF_FILE_DIR}/multifileviewer.cpp)
ADD_EXECUTABLE(multifileviewer ${multifileviewer_SOURCE})
TARGET_LINK_LIBRARIES(multifileviewer ${LINK_LIBRARY})

#overlay example
SET(overlay_SOURCE ${CONF_FILE_DIR}/overlay.cpp ${COMPUTILS_SOURCE})
ADD_EXECUTABLE(overlay ${overlay_SOURCE})
TARGET_LINK_LIBRARIES(overlay ${LINK_LIBRARY})

#planeviewer example
SET(planeviewer_SOURCE ${CONF_FILE_DIR}/planeviewer.cpp ${COMPUTILS_SOURCE})
ADD_EXECUTABLE(planeviewer ${planeviewer_SOURCE})
TARGET_LINK_LIBRARIES(planeviewer ${LINK_LIBRARY})

#renderarea example
SET(renderarea_SOURCE ${CONF_FILE_DIR}/renderarea.cpp ${COMPUTILS_SOURCE})
ADD_EXECUTABLE(renderarea ${renderarea_SOURCE})
TARGET_LINK_LIBRARIES(renderarea ${LINK_LIBRARY})

#simpleexviewer example
SET(simpleexviewer_SOURCE ${CONF_FILE_DIR}/simpleexviewer.cpp)
ADD_EXECUTABLE(simpleexviewer ${simpleexviewer_SOURCE})
TARGET_LINK_LIBRARIES(simpleexviewer ${LINK_LIBRARY})

#simplerenderarea example
SET(simplerenderarea_SOURCE ${CONF_FILE_DIR}/simplerenderarea.cpp)
ADD_EXECUTABLE(simplerenderarea ${simplerenderarea_SOURCE})
TARGET_LINK_LIBRARIES(simplerenderarea ${LINK_LIBRARY})

#snapshotviewer example
SET(snapshotviewer_SOURCE ${CONF_FILE_DIR}/snapshotviewer.cpp ${COMPUTILS_SOURCE} ${VIEWER_SOURCE})
ADD_EXECUTABLE(snapshotviewer ${snapshotviewer_SOURCE})
TARGET_LINK_LIBRARIES(snapshotviewer ${LINK_LIBRARY})

#subfullviewer example
SET(subfullviewer_SOURCE ${CONF_FILE_DIR}/subfullviewer.cpp)
ADD_EXECUTABLE(subfullviewer ${subfullviewer_SOURCE})
TARGET_LINK_LIBRARIES(subfullviewer ${LINK_LIBRARY})

#subviewer example
SET(subviewer_SOURCE ${CONF_FILE_DIR}/subviewer.cpp)
ADD_EXECUTABLE(subviewer ${subviewer_SOURCE})
TARGET_LINK_LIBRARIES(subviewer ${LINK_LIBRARY})

#walkviewer example
#SET(walkviewer_SOURCE ${CONF_FILE_DIR}/walkviewer.cpp ${COMPUTILS_SOURCE})
#ADD_EXECUTABLE(walkviewer ${walkviewer_SOURCE})
#TARGET_LINK_LIBRARIES(walkviewer ${LINK_LIBRARY})

#Generate the tree structure in the VS Projects.
SIM_VS_GENERATE_BASIC_TREE()

INSTALL(TARGETS backgroundimg RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)

IF(HAVE_DIRECTIONALLIGHTEDITOR)
INSTALL(TARGETS directionallighteditor RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)
ENDIF(HAVE_DIRECTIONALLIGHTEDITOR)

INSTALL(TARGETS examinerviewer RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)

INSTALL(TARGETS flyviewer RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)

#INSTALL(TARGETS grapheditor RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components)

IF(HAVE_SLIDERSETS)
INSTALL(TARGETS lightsliderset RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)

INSTALL(TARGETS materialsliderset RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)

INSTALL(TARGETS materialsliderset2 RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)

INSTALL(TARGETS transformsliderset RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)
ENDIF(HAVE_SLIDERSETS)

IF(HAVE_MATERIALEDITOR)
INSTALL(TARGETS materialeditor RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)
ENDIF(HAVE_MATERIALEDITOR)

IF(HAVE_MATERIALLIST)
INSTALL(TARGETS materiallist RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)

INSTALL(TARGETS materiallist2 RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)
ENDIF(HAVE_MATERIALLIST)

INSTALL(TARGETS multifileviewer RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)

INSTALL(TARGETS overlay RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)

INSTALL(TARGETS planeviewer RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)

IF(HAVE_PRINTDIALOG)
INSTALL(TARGETS printdialog RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)
ENDIF(HAVE_PRINTDIALOG)

INSTALL(TARGETS renderarea RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)

IF(HAVE_ROSTER)
INSTALL(TARGETS roster RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)
ENDIF(HAVE_ROSTER)

INSTALL(TARGETS simpleexviewer RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)

INSTALL(TARGETS simplerenderarea RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)

INSTALL(TARGETS snapshotviewer RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)

INSTALL(TARGETS subfullviewer RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)

INSTALL(TARGETS subviewer RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components
)

#INSTALL(TARGETS walkviewer RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/components)