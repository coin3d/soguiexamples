INCLUDE_DIRECTORIES(./)
SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/sensors)
INCLUDE_DIRECTORIES(${CONF_FILE_DIR})

#timersensor example
CONFIGURE_FILE(timersensor.cpp.in ${CONF_FILE_DIR}/timersensor.cpp)
SET(timersensor_SOURCE ${CONF_FILE_DIR}/timersensor.cpp)
ADD_EXECUTABLE(timersensor ${timersensor_SOURCE})
TARGET_LINK_LIBRARIES(timersensor ${LINK_LIBRARY})


#Generate the tree structure in the VS Projects.
SIM_VS_GENERATE_BASIC_TREE()

INSTALL(TARGETS timersensor
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/sensors
)