INCLUDE_DIRECTORIES(./)
SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/eyecandy)
INCLUDE_DIRECTORIES(${CONF_FILE_DIR})

#moirepatterns example
CONFIGURE_FILE(moirepatterns.cpp.in ${CONF_FILE_DIR}/moirepatterns.cpp)
SET(moirepatterns_SOURCE ${CONF_FILE_DIR}/moirepatterns.cpp)
ADD_EXECUTABLE(moirepatterns ${moirepatterns_SOURCE})
TARGET_LINK_LIBRARIES(moirepatterns ${LINK_LIBRARY})

#juliaanim example
CONFIGURE_FILE(juliaanim.cpp.in ${CONF_FILE_DIR}/juliaanim.cpp)
SET(juliaanim_SOURCE ${CONF_FILE_DIR}/juliaanim.cpp stone42a.h stone42b.h sky10a.h sky10b.h)
ADD_EXECUTABLE(juliaanim ${juliaanim_SOURCE})
TARGET_LINK_LIBRARIES(juliaanim ${LINK_LIBRARY})

#mandelzoom example
CONFIGURE_FILE(mandelzoom.cpp.in ${CONF_FILE_DIR}/mandelzoom.cpp)
SET(mandelzoom_SOURCE ${CONF_FILE_DIR}/mandelzoom.cpp stone42a.h stone42b.h sky10a.h sky10b.h)
ADD_EXECUTABLE(mandelzoom ${mandelzoom_SOURCE})
TARGET_LINK_LIBRARIES(mandelzoom ${LINK_LIBRARY})

#blob example
CONFIGURE_FILE(blob.cpp.in ${CONF_FILE_DIR}/blob.cpp)
SET(blob_SOURCE ${CONF_FILE_DIR}/blob.cpp)
ADD_EXECUTABLE(blob ${blob_SOURCE})
TARGET_LINK_LIBRARIES(blob ${LINK_LIBRARY})

#simbuoy example
CONFIGURE_FILE(simbuoy.cpp.in ${CONF_FILE_DIR}/simbuoy.cpp)
SET(simbuoy_SOURCE ${CONF_FILE_DIR}/simbuoy.cpp)
ADD_EXECUTABLE(simbuoy ${simbuoy_SOURCE})
TARGET_LINK_LIBRARIES(simbuoy ${LINK_LIBRARY})

#toonshader example
CONFIGURE_FILE(toonshader.cpp.in ${CONF_FILE_DIR}/toonshader.cpp)
SET(toonshader_SOURCE ${CONF_FILE_DIR}/toonshader.cpp)
ADD_EXECUTABLE(toonshader ${toonshader_SOURCE})
TARGET_LINK_LIBRARIES(toonshader ${LINK_LIBRARY})


#Generate the tree structure in the VS Projects.
SIM_VS_GENERATE_BASIC_TREE()

INSTALL(TARGETS moirepatterns
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/eyecandy
)

INSTALL(TARGETS juliaanim
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/eyecandy
)

INSTALL(TARGETS mandelzoom
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/eyecandy
)

INSTALL(TARGETS blob
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/eyecandy
)

INSTALL(TARGETS simbuoy
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/eyecandy
)

INSTALL(TARGETS toonshader
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/eyecandy
)