include_directories(${Coin_INCLUDE_DIR}/Inventor/annex)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#hardcopy example
configure_file(hardcopy.cpp.in hardcopy.cpp)
add_executable(hardcopy ${CMAKE_CURRENT_BINARY_DIR}/hardcopy.cpp)
target_link_libraries(hardcopy PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS hardcopy RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/annex)

#rawhardcopy example
configure_file(rawhardcopy.cpp rawhardcopy.cpp)
add_executable(rawhardcopy ${CMAKE_CURRENT_BINARY_DIR}/rawhardcopy.cpp)
target_link_libraries(rawhardcopy PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS rawhardcopy RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/annex)
