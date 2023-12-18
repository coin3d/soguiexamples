set(CMAKE_INCLUDE_CURRENT_DIR ON)

#jackdragger example
configure_file(jackdragger.cpp.in jackdragger.cpp)
add_executable(jackdragger ${CMAKE_CURRENT_BINARY_DIR}/jackdragger.cpp)
target_link_libraries(jackdragger PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS jackdragger RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/draggers)

#translate1 example
configure_file(translate1.cpp.in translate1.cpp)
add_executable(translate1 ${CMAKE_CURRENT_BINARY_DIR}/translate1.cpp)
target_link_libraries(translate1 PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS translate1 RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/draggers)

#translate2 example
configure_file(translate2.cpp.in translate2.cpp)
add_executable(translate2 ${CMAKE_CURRENT_BINARY_DIR}/translate2.cpp)
target_link_libraries(translate2 PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS translate2 RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/draggers)

#dragpoint example
configure_file(dragpoint.cpp.in dragpoint.cpp)
add_executable(dragpoint ${CMAKE_CURRENT_BINARY_DIR}/dragpoint.cpp)
target_link_libraries(dragpoint PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS dragpoint RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/draggers)
