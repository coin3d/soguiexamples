include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#blocks example
configure_file(blocks.cpp.in blocks.cpp)
add_executable(blocks ${CMAKE_CURRENT_BINARY_DIR}/blocks.cpp)
target_link_libraries(blocks PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS blocks RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)
