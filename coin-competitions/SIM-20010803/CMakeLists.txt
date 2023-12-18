set(CMAKE_INCLUDE_CURRENT_DIR ON)

#chart example
configure_file(chart.cpp.in chart.cpp)
add_executable(chart ${CMAKE_CURRENT_BINARY_DIR}/chart.cpp)
target_link_libraries(chart PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS chart RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)

#plasmafun example
configure_file(plasmafun.cpp.in plasmafun.cpp)
add_executable(plasmafun ${CMAKE_CURRENT_BINARY_DIR}/plasmafun.cpp)
target_link_libraries(plasmafun PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS plasmafun RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)

#stars example
configure_file(stars.cpp.in stars.cpp)
add_executable(stars ${CMAKE_CURRENT_BINARY_DIR}/stars.cpp envq_raw.h star_raw.h)
target_link_libraries(stars PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS stars RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)
