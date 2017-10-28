INCLUDE_DIRECTORIES(./)
SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/nodekits)
INCLUDE_DIRECTORIES(${CONF_FILE_DIR})

#scalemarker example
if (SIMVoleon_FOUND)
  CONFIGURE_FILE(scalemarker.cpp.in ${CONF_FILE_DIR}/scalemarker.cpp)
  SET(scalemarker_SOURCE ${CONF_FILE_DIR}/scalemarker.cpp)
  ADD_EXECUTABLE(scalemarker ${scalemarker_SOURCE})
  TARGET_LINK_LIBRARIES(scalemarker ${LINK_LIBRARY})
endif()

#wavekitdemo example
CONFIGURE_FILE(wavekitdemo.cpp.in ${CONF_FILE_DIR}/wavekitdemo.cpp)
SET(wavekitdemo_SOURCE ${CONF_FILE_DIR}/wavekitdemo.cpp WaveSurfaceKit.cpp WaveSurfaceKit.h)
ADD_EXECUTABLE(wavekitdemo ${wavekitdemo_SOURCE})
TARGET_LINK_LIBRARIES(wavekitdemo ${LINK_LIBRARY})

# copy over the textures pic
CONFIGURE_FILE(textures/envmap.jpg ${CONF_FILE_DIR}/textures/envmap.jpg COPYONLY)

CONFIGURE_FILE(textures/stone.jpg ${CONF_FILE_DIR}/textures/stone.jpg COPYONLY)

CONFIGURE_FILE(textures/stone2.jpg ${CONF_FILE_DIR}/textures/stone2.jpg COPYONLY)

CONFIGURE_FILE(textures/wood2.jpg ${CONF_FILE_DIR}/textures/wood2.jpg COPYONLY)


#Generate the tree structure in the VS Projects.
SIM_VS_GENERATE_BASIC_TREE()

if (SIMVoleon_FOUND)
  INSTALL(TARGETS scalemarker RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodekits)
endif()

INSTALL(TARGETS wavekitdemo
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/nodekits
)


#copy the textures directory to debug directory
INSTALL(DIRECTORY ./textures/ DESTINATION ${CURRENT_BUILD_DIR}/nodekits/textures
        FILES_MATCHING PATTERN "*.jpg"
        PATTERN ".hg" EXCLUDE)
