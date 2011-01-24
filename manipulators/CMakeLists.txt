INCLUDE_DIRECTORIES(./)
SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/manipulators)
INCLUDE_DIRECTORIES(${CONF_FILE_DIR})

#pointlightmanip example
CONFIGURE_FILE(pointlightmanip.cpp.in ${CONF_FILE_DIR}/pointlightmanip.cpp)
SET(pointlightmanip_SOURCE ${CONF_FILE_DIR}/pointlightmanip.cpp)
ADD_EXECUTABLE(pointlightmanip ${pointlightmanip_SOURCE})
TARGET_LINK_LIBRARIES(pointlightmanip ${LINK_LIBRARY})

#tabboxmanip example
CONFIGURE_FILE(tabboxmanip.cpp.in ${CONF_FILE_DIR}/tabboxmanip.cpp)
SET(tabboxmanip_SOURCE ${CONF_FILE_DIR}/tabboxmanip.cpp)
ADD_EXECUTABLE(tabboxmanip ${tabboxmanip_SOURCE})
TARGET_LINK_LIBRARIES(tabboxmanip ${LINK_LIBRARY})

#Generate the tree structure in the VS Projects.
SIM_VS_GENERATE_BASIC_TREE()

INSTALL(TARGETS pointlightmanip
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/manipulators
)

INSTALL(TARGETS tabboxmanip
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/manipulators
)