include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#25bc5bb example
configure_file(25bc5bb.cpp.in 25bc5bb.cpp)
add_executable(25bc5bb ${CMAKE_CURRENT_BINARY_DIR}/25bc5bb.cpp)
target_link_libraries(25bc5bb PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS 25bc5bb RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)

#foo example
configure_file(foo.cpp.in foo.cpp)
add_executable(foo ${CMAKE_CURRENT_BINARY_DIR}/foo.cpp)
target_link_libraries(foo PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS foo RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)

#shaker example
configure_file(shaker.cpp.in shaker.cpp)
add_executable(shaker ${CMAKE_CURRENT_BINARY_DIR}/shaker.cpp)
target_link_libraries(shaker PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS shaker RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)
