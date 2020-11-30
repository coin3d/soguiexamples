include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#audiocallback example
configure_file(audiocallback.cpp.in audiocallback.cpp)
add_executable(audiocallback ${CMAKE_CURRENT_BINARY_DIR}/audiocallback.cpp)
target_link_libraries(audiocallback PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS audiocallback RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/sound)

#manysources example
configure_file(manysources.cpp.in manysources.cpp)
add_executable(manysources ${CMAKE_CURRENT_BINARY_DIR}/manysources.cpp)
target_link_libraries(manysources PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS manysources RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/sound)

#interactive example
configure_file(interactive.cpp.in interactive.cpp)
add_executable(interactive ${CMAKE_CURRENT_BINARY_DIR}/interactive.cpp)
target_link_libraries(interactive PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS interactive RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/sound)

#copy files to build directory
file(COPY clips/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/clips FILES_MATCHING PATTERN "*.ogg" PATTERN "*.wav")
file(COPY distance_attenuation.iv head.iv remote_listener.iv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#copy files to install directory
install(DIRECTORY clips/ DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/sound/clips
  FILES_MATCHING PATTERN "*.ogg" PATTERN "*.wav"
)

install(FILES distance_attenuation.iv head.iv remote_listener.iv DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/sound/)
