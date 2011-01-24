INCLUDE_DIRECTORIES(./)
SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/actions)
INCLUDE_DIRECTORIES(${CONF_FILE_DIR})

#intersection example
CONFIGURE_FILE(intersection.cpp.in ${CONF_FILE_DIR}/intersection.cpp)
SET(intersection_SOURCE ${CONF_FILE_DIR}/intersection.cpp)
ADD_EXECUTABLE(intersection ${intersection_SOURCE})
TARGET_LINK_LIBRARIES(intersection ${LINK_LIBRARY})

#search example
CONFIGURE_FILE(search.cpp.in ${CONF_FILE_DIR}/search.cpp)
SET(search_SOURCE ${CONF_FILE_DIR}/search.cpp)
ADD_EXECUTABLE(search ${search_SOURCE})
TARGET_LINK_LIBRARIES(search ${LINK_LIBRARY})

#tesselate example
CONFIGURE_FILE(tesselate.cpp ${CONF_FILE_DIR}/tesselate.cpp)
SET(tesselate_SOURCE ${CONF_FILE_DIR}/tesselate.cpp)
ADD_EXECUTABLE(tesselate ${tesselate_SOURCE})
TARGET_LINK_LIBRARIES(tesselate ${LINK_LIBRARY})

#ivcopy example
CONFIGURE_FILE(ivcopy.cpp ${CONF_FILE_DIR}/ivcopy.cpp)
SET(ivcopy_SOURCE ${CONF_FILE_DIR}/ivcopy.cpp)
ADD_EXECUTABLE(ivcopy ${ivcopy_SOURCE})
TARGET_LINK_LIBRARIES(ivcopy ${LINK_LIBRARY})

#matrixtransform example
CONFIGURE_FILE(matrixtransform.cpp ${CONF_FILE_DIR}/matrixtransform.cpp)
SET(matrixtransform_SOURCE ${CONF_FILE_DIR}/matrixtransform.cpp)
ADD_EXECUTABLE(matrixtransform ${matrixtransform_SOURCE})
TARGET_LINK_LIBRARIES(matrixtransform ${LINK_LIBRARY})

#raypick example
CONFIGURE_FILE(raypick.cpp.in ${CONF_FILE_DIR}/raypick.cpp)
SET(raypick_SOURCE ${CONF_FILE_DIR}/raypick.cpp)
ADD_EXECUTABLE(raypick ${raypick_SOURCE})
TARGET_LINK_LIBRARIES(raypick ${LINK_LIBRARY})




#Generate the tree structure in the VS Projects.
SIM_VS_GENERATE_BASIC_TREE()

INSTALL(TARGETS intersection
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/actions
)
INSTALL(TARGETS ivcopy
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/actions
)
INSTALL(TARGETS matrixtransform
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/actions
)
INSTALL(TARGETS raypick
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/actions
)
INSTALL(TARGETS search
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/actions
)
INSTALL(TARGETS tesselate
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/actions
)