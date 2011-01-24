INCLUDE_DIRECTORIES(./)
INCLUDE_DIRECTORIES(${Coin_INCLUDE_DIR}/Inventor/annex)
SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/annex)
INCLUDE_DIRECTORIES(${CONF_FILE_DIR})

#hardcopy example
CONFIGURE_FILE(hardcopy.cpp.in ${CONF_FILE_DIR}/hardcopy.cpp)
SET(hardcopy_SOURCE ${CONF_FILE_DIR}/hardcopy.cpp)
ADD_EXECUTABLE(hardcopy ${hardcopy_SOURCE})
TARGET_LINK_LIBRARIES(hardcopy ${LINK_LIBRARY})

#rawhardcopy example
CONFIGURE_FILE(rawhardcopy.cpp ${CONF_FILE_DIR}/rawhardcopy.cpp)
SET(rawhardcopy_SOURCE ${CONF_FILE_DIR}/rawhardcopy.cpp)
ADD_EXECUTABLE(rawhardcopy ${rawhardcopy_SOURCE})
TARGET_LINK_LIBRARIES(rawhardcopy ${LINK_LIBRARY})

#Generate the tree structure in the VS Projects.
SIM_VS_GENERATE_BASIC_TREE()

INSTALL(TARGETS hardcopy
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/annex
)
INSTALL(TARGETS rawhardcopy
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/annex
)