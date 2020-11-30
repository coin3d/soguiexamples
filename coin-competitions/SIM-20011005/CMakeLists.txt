include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#lorenz example
configure_file(lorenz.cpp.in lorenz.cpp)
add_executable(lorenz ${CMAKE_CURRENT_BINARY_DIR}/lorenz.cpp star.h)
target_link_libraries(lorenz PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS lorenz RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)

#nurbscurve example
configure_file(nurbscurve.cpp.in nurbscurve.cpp)
add_executable(nurbscurve ${CMAKE_CURRENT_BINARY_DIR}/nurbscurve.cpp)
target_link_libraries(nurbscurve PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS nurbscurve RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)

#cubes example
configure_file(cubes.cpp.in cubes.cpp)
add_executable(cubes ${CMAKE_CURRENT_BINARY_DIR}/cubes.cpp Board.cpp Board.h GameLogic.cpp GameLogic.h Minimax.cpp Minimax.h TextureWriter.h TextureWriter.cpp bitmapfont8x12.h)
target_link_libraries(cubes PRIVATE ${SOGUIEXAMPLES_LINK_LIBRARIES})
install(TARGETS cubes RUNTIME DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/So${Gui}Examples/coin-competitions)
