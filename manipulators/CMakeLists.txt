set(CMAKE_INCLUDE_CURRENT_DIR ON)

#pointlightmanip example
configure_file(pointlightmanip.cpp.in pointlightmanip.cpp)
add_executable(pointlightmanip ${CMAKE_CURRENT_BINARY_DIR}/pointlightmanip.cpp)
target_link_libraries(pointlightmanip PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS pointlightmanip RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/manipulators)

#tabboxmanip example
configure_file(tabboxmanip.cpp.in tabboxmanip.cpp)
add_executable(tabboxmanip ${CMAKE_CURRENT_BINARY_DIR}/tabboxmanip.cpp)
target_link_libraries(tabboxmanip PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS tabboxmanip RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/manipulators)
