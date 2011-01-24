INCLUDE_DIRECTORIES(./)
SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/draggers)
INCLUDE_DIRECTORIES(${CONF_FILE_DIR})

#jackdragger example
CONFIGURE_FILE(jackdragger.cpp.in ${CONF_FILE_DIR}/jackdragger.cpp)
SET(jackdragger_SOURCE ${CONF_FILE_DIR}/jackdragger.cpp)
ADD_EXECUTABLE(jackdragger ${jackdragger_SOURCE})
TARGET_LINK_LIBRARIES(jackdragger ${LINK_LIBRARY})

#translate1 example
CONFIGURE_FILE(translate1.cpp.in ${CONF_FILE_DIR}/translate1.cpp)
SET(translate1_SOURCE ${CONF_FILE_DIR}/translate1.cpp)
ADD_EXECUTABLE(translate1 ${translate1_SOURCE})
TARGET_LINK_LIBRARIES(translate1 ${LINK_LIBRARY})

#translate2 example
CONFIGURE_FILE(translate2.cpp.in ${CONF_FILE_DIR}/translate2.cpp)
SET(translate2_SOURCE ${CONF_FILE_DIR}/translate2.cpp)
ADD_EXECUTABLE(translate2 ${translate2_SOURCE})
TARGET_LINK_LIBRARIES(translate2 ${LINK_LIBRARY})

#dragpoint example
CONFIGURE_FILE(dragpoint.cpp.in ${CONF_FILE_DIR}/dragpoint.cpp)
SET(dragpoint_SOURCE ${CONF_FILE_DIR}/dragpoint.cpp)
ADD_EXECUTABLE(dragpoint ${dragpoint_SOURCE})
TARGET_LINK_LIBRARIES(dragpoint ${LINK_LIBRARY})


#Generate the tree structure in the VS Projects.
SIM_VS_GENERATE_BASIC_TREE()

INSTALL(TARGETS jackdragger
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/draggers
)

INSTALL(TARGETS translate1
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/draggers
)

INSTALL(TARGETS translate2
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/draggers
)

INSTALL(TARGETS dragpoint
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/draggers
)