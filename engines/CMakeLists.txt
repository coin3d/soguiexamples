include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#computebbox example
configure_file(computebbox.cpp.in computebbox.cpp)
add_executable(computebbox ${CMAKE_CURRENT_BINARY_DIR}/computebbox.cpp)
target_link_libraries(computebbox PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS computebbox RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/engines)

#computexfbbox example
configure_file(computexfbbox.cpp.in computexfbbox.cpp)
add_executable(computexfbbox ${CMAKE_CURRENT_BINARY_DIR}/computexfbbox.cpp ComputeXfBoundingBox.cpp ComputeXfBoundingBox.h)
target_link_libraries(computexfbbox PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS computexfbbox RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/engines)
