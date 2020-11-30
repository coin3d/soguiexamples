include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#smiley example
configure_file(smiley.cpp.in smiley.cpp)
add_executable(smiley ${CMAKE_CURRENT_BINARY_DIR}/smiley.cpp)
target_link_libraries(smiley PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS smiley RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)

#plasmaball example
configure_file(plasmaball.cpp.in plasmaball.cpp)
add_executable(plasmaball ${CMAKE_CURRENT_BINARY_DIR}/plasmaball.cpp)
target_link_libraries(plasmaball PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS plasmaball RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)

#styx example
configure_file(styx.cpp.in styx.cpp)
add_executable(styx ${CMAKE_CURRENT_BINARY_DIR}/styx.cpp)
target_link_libraries(styx PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS styx RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)

#stars2 example
configure_file(stars2.cpp.in stars2.cpp)
add_executable(stars2 ${CMAKE_CURRENT_BINARY_DIR}/stars2.cpp envq_raw.h star_raw.h)
target_link_libraries(stars2 PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS stars2 RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)
