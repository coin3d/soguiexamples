INCLUDE_DIRECTORIES(./)
SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/engines)
INCLUDE_DIRECTORIES(${CONF_FILE_DIR})

#computebbox example
CONFIGURE_FILE(computebbox.cpp.in ${CONF_FILE_DIR}/computebbox.cpp)
SET(computebbox_SOURCE ${CONF_FILE_DIR}/computebbox.cpp)
ADD_EXECUTABLE(computebbox ${computebbox_SOURCE})
TARGET_LINK_LIBRARIES(computebbox ${LINK_LIBRARY})

#computexfbbox example
CONFIGURE_FILE(computexfbbox.cpp.in ${CONF_FILE_DIR}/computexfbbox.cpp)
SET(computexfbbox_SOURCE ${CONF_FILE_DIR}/computexfbbox.cpp ComputeXfBoundingBox.cpp ComputeXfBoundingBox.h)
ADD_EXECUTABLE(computexfbbox ${computexfbbox_SOURCE})
TARGET_LINK_LIBRARIES(computexfbbox ${LINK_LIBRARY})


#Generate the tree structure in the VS Projects.
SIM_VS_GENERATE_BASIC_TREE()

INSTALL(TARGETS computebbox
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/engines
)

INSTALL(TARGETS computexfbbox
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/engines
)