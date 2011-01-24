INCLUDE_DIRECTORIES(./)
SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/sound)
INCLUDE_DIRECTORIES(${CONF_FILE_DIR})

#audiocallback example
CONFIGURE_FILE(audiocallback.cpp.in ${CONF_FILE_DIR}/audiocallback.cpp)
SET(audiocallback_SOURCE ${CONF_FILE_DIR}/audiocallback.cpp)
ADD_EXECUTABLE(audiocallback ${audiocallback_SOURCE})
TARGET_LINK_LIBRARIES(audiocallback ${LINK_LIBRARY})

#manysources example
CONFIGURE_FILE(manysources.cpp.in ${CONF_FILE_DIR}/manysources.cpp)
SET(manysources_SOURCE ${CONF_FILE_DIR}/manysources.cpp)
ADD_EXECUTABLE(manysources ${manysources_SOURCE})
TARGET_LINK_LIBRARIES(manysources ${LINK_LIBRARY})

#interactive example
CONFIGURE_FILE(interactive.cpp.in ${CONF_FILE_DIR}/interactive.cpp)
SET(interactive_SOURCE ${CONF_FILE_DIR}/interactive.cpp)
ADD_EXECUTABLE(interactive ${interactive_SOURCE})
TARGET_LINK_LIBRARIES(interactive ${LINK_LIBRARY})

# copy over the .wav .ogg .iv files
CONFIGURE_FILE(clips/brokenglass.wav ${CONF_FILE_DIR}/clips/brokenglass.wav COPYONLY)

CONFIGURE_FILE(clips/bubbles1.wav ${CONF_FILE_DIR}/clips/bubbles1.wav COPYONLY)

CONFIGURE_FILE(clips/dunk1.wav ${CONF_FILE_DIR}/clips/dunk1.wav COPYONLY)

CONFIGURE_FILE(clips/dunk2.wav ${CONF_FILE_DIR}/clips/dunk2.wav COPYONLY)

CONFIGURE_FILE(clips/dunk3.wav ${CONF_FILE_DIR}/clips/dunk3.wav COPYONLY)

CONFIGURE_FILE(clips/ticktack.wav ${CONF_FILE_DIR}/clips/ticktack.wav COPYONLY)

CONFIGURE_FILE(clips/drumloop_a.ogg ${CONF_FILE_DIR}/clips/drumloop_a.ogg COPYONLY)

CONFIGURE_FILE(clips/synthloop_a.ogg ${CONF_FILE_DIR}/clips/synthloop_a.ogg COPYONLY)

CONFIGURE_FILE(clips/synthloop_b.ogg ${CONF_FILE_DIR}/clips/synthloop_b.ogg COPYONLY)

CONFIGURE_FILE(distance_attenuation.iv ${CONF_FILE_DIR}/distance_attenuation.iv COPYONLY)

CONFIGURE_FILE(head.iv ${CONF_FILE_DIR}/head.iv COPYONLY)

CONFIGURE_FILE(remote_listener.iv ${CONF_FILE_DIR}/remote_listener.iv COPYONLY)


#Generate the tree structure in the VS Projects.
SIM_VS_GENERATE_BASIC_TREE()

INSTALL(TARGETS audiocallback
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/sound
)

INSTALL(TARGETS manysources
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/sound
)

INSTALL(TARGETS interactive
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/sound
)


#copy files to install directory
INSTALL(DIRECTORY ./clips/ DESTINATION ${CONF_FILE_DIR}/sound/clips
        FILES_MATCHING PATTERN "*"
        PATTERN ".hg" EXCLUDE)

INSTALL(DIRECTORY ./ DESTINATION ${CONF_FILE_DIR}/sound
        FILES_MATCHING PATTERN "*.iv"
        PATTERN ".hg" EXCLUDE)