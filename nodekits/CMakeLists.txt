include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#scalemarker example
if(SIMVoleon_FOUND)
  configure_file(scalemarker.cpp.in scalemarker.cpp)
  add_executable(scalemarker ${CMAKE_CURRENT_BINARY_DIR}/scalemarker.cpp)
  target_link_libraries(scalemarker PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
  install(TARGETS scalemarker RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodekits)
endif()

#wavekitdemo example
configure_file(wavekitdemo.cpp.in wavekitdemo.cpp)
add_executable(wavekitdemo ${CMAKE_CURRENT_BINARY_DIR}/wavekitdemo.cpp WaveSurfaceKit.cpp WaveSurfaceKit.h)
target_link_libraries(wavekitdemo PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS wavekitdemo RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodekits)

#copy textures to build directory
file(COPY textures/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/textures FILES_MATCHING PATTERN "*.jpg")

#copy the textures directory to install directory
install(DIRECTORY textures/ DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/nodekits/textures
  FILES_MATCHING PATTERN "*.jpg"
)
