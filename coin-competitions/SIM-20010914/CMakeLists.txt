set(CMAKE_INCLUDE_CURRENT_DIR ON)

#moolah example
configure_file(Moolah.cpp.in Moolah.cpp)
add_executable(moolah ${CMAKE_CURRENT_BINARY_DIR}/Moolah.cpp MooExecutive.cpp MooExecutive.h MooList.cpp MooList.h MooOut.cpp MooOut.h MooString.cpp MooString.h MooTokenizer.cpp MooTokenizer.h font.h)
target_link_libraries(moolah PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS moolah RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)

#calculator example
configure_file(calculator.cpp.in calculator.cpp)
add_executable(calculator ${CMAKE_CURRENT_BINARY_DIR}/calculator.cpp)
target_link_libraries(calculator PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS calculator RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)

#coinhistory example
configure_file(coinhistory.cpp.in coinhistory.cpp)
add_executable(coinhistory ${CMAKE_CURRENT_BINARY_DIR}/coinhistory.cpp)
target_link_libraries(coinhistory PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS coinhistory RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)

#kaos example
configure_file(kaos.cpp.in kaos.cpp)
add_executable(kaos ${CMAKE_CURRENT_BINARY_DIR}/kaos.cpp)
target_link_libraries(kaos PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS kaos RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)

#rec example
configure_file(rec.cpp.in rec.cpp)
add_executable(rec ${CMAKE_CURRENT_BINARY_DIR}/rec.cpp)
target_link_libraries(rec PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS rec RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)
