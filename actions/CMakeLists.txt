set(CMAKE_INCLUDE_CURRENT_DIR ON)

#intersection example
configure_file(intersection.cpp.in intersection.cpp)
add_executable(intersection ${CMAKE_CURRENT_BINARY_DIR}/intersection.cpp)
target_link_libraries(intersection PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS intersection RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/actions)

#search example
configure_file(search.cpp.in search.cpp)
add_executable(search ${CMAKE_CURRENT_BINARY_DIR}/search.cpp)
target_link_libraries(search PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS search RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/actions)

#tesselate example
configure_file(tesselate.cpp tesselate.cpp)
add_executable(tesselate ${CMAKE_CURRENT_BINARY_DIR}/tesselate.cpp)
target_link_libraries(tesselate PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS tesselate RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/actions)

#ivcopy example
configure_file(ivcopy.cpp ivcopy.cpp)
add_executable(ivcopy ${CMAKE_CURRENT_BINARY_DIR}/ivcopy.cpp)
target_link_libraries(ivcopy PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS ivcopy RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/actions)

#matrixtransform example
configure_file(matrixtransform.cpp matrixtransform.cpp)
add_executable(matrixtransform ${CMAKE_CURRENT_BINARY_DIR}/matrixtransform.cpp)
target_link_libraries(matrixtransform PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS matrixtransform RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/actions)

#raypick example
configure_file(raypick.cpp.in raypick.cpp)
add_executable(raypick ${CMAKE_CURRENT_BINARY_DIR}/raypick.cpp)
target_link_libraries(raypick PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS raypick RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/actions)
