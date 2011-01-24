INCLUDE_DIRECTORIES(./)
INCLUDE_DIRECTORIES(../)
INCLUDE_DIRECTORIES(./SIM-20010803)
INCLUDE_DIRECTORIES(./SIM-20010824)
INCLUDE_DIRECTORIES(./SIM-20010914)
INCLUDE_DIRECTORIES(./SIM-20011005)
INCLUDE_DIRECTORIES(./SIM-20011116)
INCLUDE_DIRECTORIES(./SIM-20020118)
INCLUDE_DIRECTORIES(./SIM-20020503)


SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/coin-competitions/SIM-20010803)

#chart example
CONFIGURE_FILE(SIM-20010803/chart.cpp.in ${CONF_FILE_DIR}/chart.cpp)
SET(chart_SOURCE ${CONF_FILE_DIR}/chart.cpp)
ADD_EXECUTABLE(chart ${chart_SOURCE})
TARGET_LINK_LIBRARIES(chart ${LINK_LIBRARY})

#plasmafun example
CONFIGURE_FILE(SIM-20010803/plasmafun.cpp.in ${CONF_FILE_DIR}/plasmafun.cpp)
SET(plasmafun_SOURCE ${CONF_FILE_DIR}/plasmafun.cpp)
ADD_EXECUTABLE(plasmafun ${plasmafun_SOURCE})
TARGET_LINK_LIBRARIES(plasmafun ${LINK_LIBRARY})

#stars example
CONFIGURE_FILE(SIM-20010803/stars.cpp.in ${CONF_FILE_DIR}/stars.cpp)
SET(stars_SOURCE ${CONF_FILE_DIR}/stars.cpp SIM-20010803/envq_raw.h SIM-20010803/star_raw.h)
ADD_EXECUTABLE(stars ${stars_SOURCE})
TARGET_LINK_LIBRARIES(stars ${LINK_LIBRARY})
###################################

SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/coin-competitions/SIM-20010824)

#smiley example
CONFIGURE_FILE(SIM-20010824/smiley.cpp.in ${CONF_FILE_DIR}/smiley.cpp)
SET(smiley_SOURCE ${CONF_FILE_DIR}/smiley.cpp)
ADD_EXECUTABLE(smiley ${smiley_SOURCE})
TARGET_LINK_LIBRARIES(smiley ${LINK_LIBRARY})

#plasmaball example
CONFIGURE_FILE(SIM-20010824/plasmaball.cpp.in ${CONF_FILE_DIR}/plasmaball.cpp)
SET(plasmaball_SOURCE ${CONF_FILE_DIR}/plasmaball.cpp)
ADD_EXECUTABLE(plasmaball ${plasmaball_SOURCE})
TARGET_LINK_LIBRARIES(plasmaball ${LINK_LIBRARY})

#styx example
CONFIGURE_FILE(SIM-20010824/styx.cpp.in ${CONF_FILE_DIR}/styx.cpp)
SET(styx_SOURCE ${CONF_FILE_DIR}/styx.cpp)
ADD_EXECUTABLE(styx ${styx_SOURCE})
TARGET_LINK_LIBRARIES(styx ${LINK_LIBRARY})

#stars2 example
CONFIGURE_FILE(SIM-20010824/stars2.cpp.in ${CONF_FILE_DIR}/stars2.cpp)
SET(stars2_SOURCE ${CONF_FILE_DIR}/stars2.cpp SIM-20010824/envq_raw.h SIM-20010824/star_raw.h)
ADD_EXECUTABLE(stars2 ${stars2_SOURCE})
TARGET_LINK_LIBRARIES(stars2 ${LINK_LIBRARY})
##################################

SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/coin-competitions/SIM-20010914)

#moolah example
CONFIGURE_FILE(SIM-20010914/Moolah.cpp.in ${CONF_FILE_DIR}/Moolah.cpp)
SET(moolah_SOURCE ${CONF_FILE_DIR}/Moolah.cpp SIM-20010914/MooExecutive.cpp SIM-20010914/MooExecutive.h SIM-20010914/MooList.cpp SIM-20010914/MooList.h SIM-20010914/MooOut.cpp SIM-20010914/MooOut.h SIM-20010914/MooString.cpp SIM-20010914/MooString.h SIM-20010914/MooTokenizer.cpp SIM-20010914/MooTokenizer.h SIM-20010914/font.h)
ADD_EXECUTABLE(moolah ${moolah_SOURCE})
TARGET_LINK_LIBRARIES(moolah ${LINK_LIBRARY})

#calculator example
CONFIGURE_FILE(SIM-20010914/calculator.cpp.in ${CONF_FILE_DIR}/calculator.cpp)
SET(calculator_SOURCE ${CONF_FILE_DIR}/calculator.cpp)
ADD_EXECUTABLE(calculator ${calculator_SOURCE})
TARGET_LINK_LIBRARIES(calculator ${LINK_LIBRARY})

#coinhistory example
CONFIGURE_FILE(SIM-20010914/coinhistory.cpp.in ${CONF_FILE_DIR}/coinhistory.cpp)
SET(coinhistory_SOURCE ${CONF_FILE_DIR}/coinhistory.cpp)
ADD_EXECUTABLE(coinhistory ${coinhistory_SOURCE})
TARGET_LINK_LIBRARIES(coinhistory ${LINK_LIBRARY})

#kaos example
CONFIGURE_FILE(SIM-20010914/kaos.cpp.in ${CONF_FILE_DIR}/kaos.cpp)
SET(kaos_SOURCE ${CONF_FILE_DIR}/kaos.cpp)
ADD_EXECUTABLE(kaos ${kaos_SOURCE})
TARGET_LINK_LIBRARIES(kaos ${LINK_LIBRARY})

#rec example
CONFIGURE_FILE(SIM-20010914/rec.cpp.in ${CONF_FILE_DIR}/rec.cpp)
SET(rec_SOURCE ${CONF_FILE_DIR}/rec.cpp)
ADD_EXECUTABLE(rec ${rec_SOURCE})
TARGET_LINK_LIBRARIES(rec ${LINK_LIBRARY})
#####################################

SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/coin-competitions/SIM-20011005)

#lorenz example
CONFIGURE_FILE(SIM-20011005/lorenz.cpp.in ${CONF_FILE_DIR}/lorenz.cpp)
SET(lorenz_SOURCE ${CONF_FILE_DIR}/lorenz.cpp SIM-20011005/star.h)
ADD_EXECUTABLE(lorenz ${lorenz_SOURCE})
TARGET_LINK_LIBRARIES(lorenz ${LINK_LIBRARY})

#nurbscurve example
CONFIGURE_FILE(SIM-20011005/nurbscurve.cpp.in ${CONF_FILE_DIR}/nurbscurve.cpp)
SET(nurbscurve_SOURCE ${CONF_FILE_DIR}/nurbscurve.cpp)
ADD_EXECUTABLE(nurbscurve ${nurbscurve_SOURCE})
TARGET_LINK_LIBRARIES(nurbscurve ${LINK_LIBRARY})

#cubes example
CONFIGURE_FILE(SIM-20011005/cubes.cpp.in ${CONF_FILE_DIR}/cubes.cpp)
SET(cubes_SOURCE ${CONF_FILE_DIR}/cubes.cpp SIM-20011005/Board.cpp SIM-20011005/Board.h SIM-20011005/GameLogic.cpp SIM-20011005/GameLogic.h SIM-20011005/Minimax.cpp SIM-20011005/Minimax.h TextureWriter.h TextureWriter.cpp bitmapfont8x12.h)
ADD_EXECUTABLE(cubes ${cubes_SOURCE})
TARGET_LINK_LIBRARIES(cubes ${LINK_LIBRARY})
##################################

SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/coin-competitions/SIM-20011116)

#25bc5bb example
CONFIGURE_FILE(SIM-20011116/25bc5bb.cpp.in ${CONF_FILE_DIR}/25bc5bb.cpp)
SET(25bc5bb_SOURCE ${CONF_FILE_DIR}/25bc5bb.cpp)
ADD_EXECUTABLE(25bc5bb ${25bc5bb_SOURCE})
TARGET_LINK_LIBRARIES(25bc5bb ${LINK_LIBRARY})

#foo example
CONFIGURE_FILE(SIM-20011116/foo.cpp.in ${CONF_FILE_DIR}/foo.cpp)
SET(foo_SOURCE ${CONF_FILE_DIR}/foo.cpp)
ADD_EXECUTABLE(foo ${foo_SOURCE})
TARGET_LINK_LIBRARIES(foo ${LINK_LIBRARY})

#shaker example
CONFIGURE_FILE(SIM-20011116/shaker.cpp.in ${CONF_FILE_DIR}/shaker.cpp)
SET(shaker_SOURCE ${CONF_FILE_DIR}/shaker.cpp simlogo.h)
ADD_EXECUTABLE(shaker ${shaker_SOURCE})
TARGET_LINK_LIBRARIES(shaker ${LINK_LIBRARY})
#####################################

SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/coin-competitions/SIM-20020118)

#blocks example
CONFIGURE_FILE(SIM-20020118/blocks.cpp.in ${CONF_FILE_DIR}/blocks.cpp)
SET(blocks_SOURCE ${CONF_FILE_DIR}/blocks.cpp)
ADD_EXECUTABLE(blocks ${blocks_SOURCE})
TARGET_LINK_LIBRARIES(blocks ${LINK_LIBRARY})
#######################################

SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/coin-competitions/SIM-20020503)

#ballinthehoop example
CONFIGURE_FILE(SIM-20020503/ballinthehoop.cpp.in ${CONF_FILE_DIR}/ballinthehoop.cpp)
SET(ballinthehoop_SOURCE ${CONF_FILE_DIR}/ballinthehoop.cpp)
ADD_EXECUTABLE(ballinthehoop ${ballinthehoop_SOURCE})
TARGET_LINK_LIBRARIES(ballinthehoop ${LINK_LIBRARY})

#flow example
CONFIGURE_FILE(SIM-20020503/flow.cpp.in ${CONF_FILE_DIR}/flow.cpp)
SET(flow_SOURCE ${CONF_FILE_DIR}/flow.cpp)
ADD_EXECUTABLE(flow ${flow_SOURCE})
TARGET_LINK_LIBRARIES(flow ${LINK_LIBRARY})

#typeomatic example
CONFIGURE_FILE(SIM-20020503/typeomatic.cpp.in ${CONF_FILE_DIR}/typeomatic.cpp)
SET(typeomatic_SOURCE ${CONF_FILE_DIR}/typeomatic.cpp strutils.h strutils.cpp)
ADD_EXECUTABLE(typeomatic ${typeomatic_SOURCE})
TARGET_LINK_LIBRARIES(typeomatic ${LINK_LIBRARY})
######################################

SET(CONF_FILE_DIR ${PROJECT_BINARY_DIR}/coin-competitions)

#Generate the tree structure in the VS Projects.
SIM_VS_GENERATE_BASIC_TREE()

INSTALL(TARGETS chart
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)
INSTALL(TARGETS plasmafun
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)
INSTALL(TARGETS stars
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)

INSTALL(TARGETS smiley
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)
INSTALL(TARGETS plasmaball
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)
INSTALL(TARGETS styx
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)
INSTALL(TARGETS stars2
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)

INSTALL(TARGETS moolah
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)
INSTALL(TARGETS calculator
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)
INSTALL(TARGETS coinhistory
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)
INSTALL(TARGETS kaos
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)
INSTALL(TARGETS rec
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)

INSTALL(TARGETS lorenz
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)
INSTALL(TARGETS nurbscurve
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)
INSTALL(TARGETS cubes
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)

INSTALL(TARGETS 25bc5bb
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)
INSTALL(TARGETS foo
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)
INSTALL(TARGETS shaker
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)

INSTALL(TARGETS blocks
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)

INSTALL(TARGETS ballinthehoop
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)

INSTALL(TARGETS flow
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)
INSTALL(TARGETS typeomatic
  RUNTIME DESTINATION ${CURRENT_BUILD_DIR}/coin-competitions
)