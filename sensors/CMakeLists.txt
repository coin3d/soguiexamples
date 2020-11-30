include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#timersensor example
configure_file(timersensor.cpp.in timersensor.cpp)
add_executable(timersensor ${CMAKE_CURRENT_BINARY_DIR}/timersensor.cpp)
target_link_libraries(timersensor PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS timersensor RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/sensors)
