set(CMAKE_INCLUDE_CURRENT_DIR ON)

#moirepatterns example
configure_file(moirepatterns.cpp.in moirepatterns.cpp)
add_executable(moirepatterns ${CMAKE_CURRENT_BINARY_DIR}/moirepatterns.cpp)
target_link_libraries(moirepatterns PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS moirepatterns RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/eyecandy)

#juliaanim example
configure_file(juliaanim.cpp.in juliaanim.cpp)
add_executable(juliaanim ${CMAKE_CURRENT_BINARY_DIR}/juliaanim.cpp stone42a.h stone42b.h sky10a.h sky10b.h)
target_link_libraries(juliaanim PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS juliaanim RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/eyecandy)

#mandelzoom example
configure_file(mandelzoom.cpp.in mandelzoom.cpp)
add_executable(mandelzoom ${CMAKE_CURRENT_BINARY_DIR}/mandelzoom.cpp stone42a.h stone42b.h sky10a.h sky10b.h)
target_link_libraries(mandelzoom PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS mandelzoom RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/eyecandy)

#blob example
configure_file(blob.cpp.in blob.cpp)
add_executable(blob ${CMAKE_CURRENT_BINARY_DIR}/blob.cpp)
target_link_libraries(blob PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS blob RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/eyecandy)

#simbuoy example
configure_file(simbuoy.cpp.in simbuoy.cpp)
add_executable(simbuoy ${CMAKE_CURRENT_BINARY_DIR}/simbuoy.cpp)
target_link_libraries(simbuoy PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS simbuoy RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/eyecandy)

#toonshader example
configure_file(toonshader.cpp.in toonshader.cpp)
add_executable(toonshader ${CMAKE_CURRENT_BINARY_DIR}/toonshader.cpp)
target_link_libraries(toonshader PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS toonshader RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/eyecandy)
