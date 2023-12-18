set(CMAKE_INCLUDE_CURRENT_DIR ON)

#ballinthehoop example
configure_file(ballinthehoop.cpp.in ballinthehoop.cpp)
add_executable(ballinthehoop ${CMAKE_CURRENT_BINARY_DIR}/ballinthehoop.cpp)
target_link_libraries(ballinthehoop PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS ballinthehoop RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)

#flow example
configure_file(flow.cpp.in flow.cpp)
add_executable(flow ${CMAKE_CURRENT_BINARY_DIR}/flow.cpp)
target_link_libraries(flow PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS flow RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)

#typeomatic example
configure_file(typeomatic.cpp.in typeomatic.cpp)
add_executable(typeomatic ${CMAKE_CURRENT_BINARY_DIR}/typeomatic.cpp strutils.h strutils.cpp)
target_link_libraries(typeomatic PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS typeomatic RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)
