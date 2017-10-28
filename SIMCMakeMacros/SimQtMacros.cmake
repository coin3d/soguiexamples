INCLUDE(SimMSVC)

# SIM_QT4_WRAP_CPP(outfiles infiles ... )
MACRO(SIM_QT4_AUTO_WRAP_CPP outfiles )
  # Clear list to be sure - QT4_WRAP_CPP doesnt do it
  # FIXME: Is this what we want, really? Several of the built-in macros
  # behave as "append", not "set" - rolvs
  SET(${outfiles} )

  FOREACH(_current_FILE ${ARGN})
    # Read file
    GET_FILENAME_COMPONENT(_abs_FILE ${_current_FILE} ABSOLUTE)
    FILE(READ ${_abs_FILE} _contents)

    # Process file
    STRING(REGEX MATCHALL "Q_OBJECT" _match "${_contents}")

    IF(_match)
      # Found a file that needs to be moc'ed, do it
      #GET_FILENAME_COMPONENT(_basename ${_current_FILE} NAME_WE)
      #SET(_moced_FILE "moc_${_basename}.cpp"}}
      QT4_WRAP_CPP(${outfiles} ${_current_FILE})
    ENDIF(_match)

  ENDFOREACH(_current_FILE)
ENDMACRO(SIM_QT4_AUTO_WRAP_CPP)

# SIM_QT4_WRAP_ALL(outfile SOURCE infiles ... [OUTFILENAME outfilename])
# Optimized version of SIM_QT4_WRAP_CPP(). This file
# concats all mocs together before compiling, potentially reducing the
# compiletime. Note that this macro requires Python.
MACRO(SIM_QT4_AUTO_WRAP_ALL outfile)
  SIM_VALIDATE_ARGUMENTS(ValidArguments SIM_QT4_AUTO_WRAP_ALL
                         "SOURCES"                               # Required
                         "OUTFILENAME;SOURCES"                   # Allowed
                         "${ARGV}")
  IF(Python_FOUND OR PYTHONINTERP_FOUND)
    SET(_python ${Python_EXECUTABLE})
  ELSE(Python_FOUND OR PYTHONINTERP_FOUND)
    MESSAGE(FATAL_ERROR "Python required to use SIM_QT4_AUTO_WRAP_ALL(). Use FindPython or FindPythonInterp to locate Python")
  ENDIF(Python_FOUND OR PYTHONINTERP_FOUND)
  # Required arguments
  SIM_FETCH_ARGUMENTS(_sources SOURCES ${ARGV})  
  # Optional arguments
  SIM_HAS_ARGUMENT(_hasOutfilename OUTFILENAME ${ARGV})
  IF(_hasOutfilename)
    SIM_FETCH_ARGUMENTS(_outfilename OUTFILENAME ${ARGV})
    SET(_mocFilename "${CMAKE_CURRENT_BINARY_DIR}/${_outfilename}")
  ELSE(_hasOutfilename)
    SET(_mocFilename "${CMAKE_CURRENT_BINARY_DIR}/__moc_joined.cxx")
  ENDIF(_hasOutfilename)
  SET(${outfile} ${_mocFilename})
    
  SET(_moccedFiles )
  FOREACH(_current_FILE ${_sources})
    # Read file
    GET_FILENAME_COMPONENT(_abs_FILE ${_current_FILE} ABSOLUTE)
    FILE(READ ${_abs_FILE} _contents)
    # Process file
    STRING(REGEX MATCHALL "Q_OBJECT" _match "${_contents}")
    IF(_match)
      QT4_WRAP_CPP(_moccedFiles ${_current_FILE})
    ENDIF(_match)
  ENDFOREACH(_current_FILE)

  # Add a target that depends on all mocced files
  # The command concats all mocced files into a big file
  LIST(LENGTH _moccedFiles _moccedFilesLen)
  IF(_moccedFilesLen GREATER 0)
    FILE(TO_NATIVE_PATH ${_mocFilename} _nativeMocFilename)
    FILE(RELATIVE_PATH _relMoccedFilename ${CMAKE_CURRENT_BINARY_DIR} ${_mocFilename})
    SET(_scriptFilename "${_mocFilename}.py")
    
    # Generate Python script
    FILE(REMOVE ${_scriptFilename})
    FILE(APPEND ${_scriptFilename} "out = file('${_mocFilename}','w')\n")
    FOREACH(_fileToMoc ${_moccedFiles})
      FILE(TO_NATIVE_PATH "${_fileToMoc}" _filePath)
      FILE(APPEND ${_scriptFilename} "out.writelines(file('${_fileToMoc}', 'r').readlines())\n")
    ENDFOREACH(_fileToMoc)
    
    # Target that uses the script
    ADD_CUSTOM_COMMAND(OUTPUT ${_mocFilename}
                       DEPENDS ${_moccedFiles}
                       COMMAND ${_python} ARGS ${_scriptFilename}
                       COMMENT "Joining ${_moccedFilesLen} mocs to ${_relMoccedFilename}"
                       VERBATIM)
  ELSE(_moccedFilesLen GREATER 0)
    SET(${outfile})
  ENDIF(_moccedFilesLen GREATER 0)
ENDMACRO(SIM_QT4_AUTO_WRAP_ALL)



# SIM_QT4_WRAP_UI_TO(outfiles todirectory inputfiles ... )
MACRO (SIM_QT4_WRAP_UI_TO outfiles todirectory )
  FOREACH (it ${ARGN})
    GET_FILENAME_COMPONENT(outfile ${it} NAME_WE)
    GET_FILENAME_COMPONENT(infile ${it} ABSOLUTE)
    SET(outfile ${CMAKE_CURRENT_BINARY_DIR}/${todirectory}/ui_${outfile}.h)
    ADD_CUSTOM_COMMAND(OUTPUT ${outfile}
      COMMAND ${QT_UIC_EXECUTABLE}
      ARGS -o ${outfile} ${infile}
      MAIN_DEPENDENCY ${infile})
    SET(${outfiles} ${${outfiles}} ${outfile})
  ENDFOREACH (it)
ENDMACRO (SIM_QT4_WRAP_UI_TO)

# SIM_QT4_ADD_RESOURCES_TO(outfiles todirectory inputfiles ... )
MACRO (SIM_QT4_ADD_RESOURCES_TO outfiles todirectory )
  SET(rcc_files ${ARGN})

  FOREACH (it ${rcc_files})
    GET_FILENAME_COMPONENT(outfilename ${it} NAME_WE)
    GET_FILENAME_COMPONENT(infile ${it} ABSOLUTE)
    GET_FILENAME_COMPONENT(rc_path ${infile} PATH)
    SET(outfile ${CMAKE_CURRENT_BINARY_DIR}/${todirectory}/qrc_${outfilename}.cxx)
    #  parse file for dependencies
    #  all files are absolute paths or relative to the location of the qrc file
    FILE(READ "${infile}" _RC_FILE_CONTENTS)
    STRING(REGEX MATCHALL "<file[^<]+" _RC_FILES "${_RC_FILE_CONTENTS}")
    SET(_RC_DEPENDS)
    FOREACH(_RC_FILE ${_RC_FILES})
      STRING(REGEX REPLACE "^<file[^>]*>" "" _RC_FILE "${_RC_FILE}")
      STRING(REGEX MATCH "^/|([A-Za-z]:/)" _ABS_PATH_INDICATOR "${_RC_FILE}")
      IF(NOT _ABS_PATH_INDICATOR)
        SET(_RC_FILE "${rc_path}/${_RC_FILE}")
      ENDIF(NOT _ABS_PATH_INDICATOR)
      SET(_RC_DEPENDS ${_RC_DEPENDS} "${_RC_FILE}")
    ENDFOREACH(_RC_FILE)
    ADD_CUSTOM_COMMAND(OUTPUT ${outfile}
      COMMAND ${QT_RCC_EXECUTABLE}
      ARGS -name ${outfilename} -o ${outfile} ${infile}
      MAIN_DEPENDENCY ${infile}
      DEPENDS ${_RC_DEPENDS})
    SET(${outfiles} ${${outfiles}} ${outfile})
  ENDFOREACH (it)
ENDMACRO(SIM_QT4_ADD_RESOURCES_TO)

# SIM_CREATE_QT4_START_JOINTRUNNER(runnername)
# Starts a block of unittests that should be compiled into
# a single runner. Add tests using SIM_CREATE_QT4_UNITTEST().
# Note that the unittests to be compiled can't have a main()
# method when SIM_JOINT_UNITTEST_RUNNER is defined.
MACRO(SIM_CREATE_QT4_START_JOINTRUNNER runnername)
  SET(JOINT_UNITTEST_RUNNERNAME ${runnername})
  SET(JOINT_UNITTEST_ENABLED TRUE)
  # Clear lists
  SET(JOINT_UNITTEST_NAMES)
  SET(JOINT_UNITTEST_HEADERS)
  SET(JOINT_UNITTEST_SOURCES)
  SET(JOINT_UNITTEST_LIBRARIES)
ENDMACRO(SIM_CREATE_QT4_START_JOINTRUNNER)

# SIM_CREATE_QT4_JOINT_TEST
# Do not use directly. Use SIM_CREATE_QT4_START_JOINTRUNNER(),
# SIM_QT4_CREATE_UNITTEST() and SIM_CREATE_QT4_END_JOINTRUNNER().
MACRO(SIM_ADD_QT4_JOINT_TEST name header source)
  LIST(APPEND JOINT_UNITTEST_NAMES ${name})
  LIST(APPEND JOINT_UNITTEST_HEADERS ${header})
  LIST(APPEND JOINT_UNITTEST_SOURCES ${source})
  LIST(APPEND JOINT_UNITTEST_LIBRARIES ${ARGN})
ENDMACRO(SIM_ADD_QT4_JOINT_TEST)

# SIM_CREATE_QT4_END_JOINTRUNNER()
# Compiles a runner for the unittests added since the last call
# to SIM_CREATE_QT4_START_JOINTRUNNER().
MACRO(SIM_CREATE_QT4_END_JOINTRUNNER)
  LIST(LENGTH JOINT_UNITTEST_NAMES _count)
  IF(${_count} GREATER 0)
    LIST(REMOVE_DUPLICATES JOINT_UNITTEST_NAMES)
    LIST(REMOVE_DUPLICATES JOINT_UNITTEST_HEADERS)
    LIST(REMOVE_DUPLICATES JOINT_UNITTEST_SOURCES)
    LIST(REMOVE_DUPLICATES JOINT_UNITTEST_LIBRARIES)

    # Generate the runner
    SET(_runner "${CMAKE_CURRENT_BINARY_DIR}/${JOINT_UNITTEST_RUNNERNAME}.cxx")
    FILE(REMOVE ${_runner})
    # #includes
    FILE(APPEND ${_runner} "#include <QtGui/QApplication>\n")
    FILE(APPEND ${_runner} "#include <QtTest/QtTest>\n")
    FILE(APPEND ${_runner} "#include <QtCore/QtGlobal>\n")
    FILE(APPEND ${_runner} "#include <QtCore/QString>\n")
    FOREACH(_header ${JOINT_UNITTEST_HEADERS})
      FILE(TO_NATIVE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${_header}" _nativeHeaderPath)
      FILE(APPEND ${_runner} "#include \"${_nativeHeaderPath}\"\n")
    ENDFOREACH(_header)
    # The main method.
    FILE(APPEND ${_runner} "int main(int argc, char * args[]) {\n")
    FILE(APPEND ${_runner} "  QApplication app(argc, args);\n")
    FILE(APPEND ${_runner} "  int result = 0;\n")
    FOREACH(_test ${JOINT_UNITTEST_NAMES})
      FILE(APPEND ${_runner} "  ${_test} ${_test}_instance;\n")
      FILE(APPEND ${_runner} "  if(argc == 1 || QString(args[1]) == \"${_test}\")"
                             "    result += QTest::qExec(&${_test}_instance);\n")
    ENDFOREACH(_test)
    FILE(APPEND ${_runner} "  return result;\n")
    FILE(APPEND ${_runner} "}\n\n")

    # Compile  
    SIM_QT4_AUTO_WRAP_ALL(Mocs SOURCES ${JOINT_UNITTEST_HEADERS} OUTFILENAME "__moc__${JOINT_UNITTEST_RUNNERNAME}.cxx")
    ADD_DEFINITIONS(-DSIM_JOINT_UNITTEST_RUNNER) 
    ADD_EXECUTABLE(${JOINT_UNITTEST_RUNNERNAME} ${_runner} ${Mocs} ${JOINT_UNITTEST_HEADERS} ${JOINT_UNITTEST_SOURCES})
    TARGET_LINK_LIBRARIES(${JOINT_UNITTEST_RUNNERNAME} ${JOINT_UNITTEST_LIBRARIES} ${QT_QTTEST_LIBRARY})

    # Add testrunners
    FOREACH(_test ${JOINT_UNITTEST_NAMES})
      ADD_TEST(${_test} ${JOINT_UNITTEST_RUNNERNAME} ${_test})
    ENDFOREACH(_test)

  ENDIF(${_count} GREATER 0)

  # Clear lists
  SET(JOINT_UNITTEST_NAMES)
  SET(JOINT_UNITTEST_HEADERS)
  SET(JOINT_UNITTEST_SOURCES)
  SET(JOINT_UNITTEST_LIBRARIES)
  SET(JOINT_UNITTEST_RUNNERNAME)
  SET(JOINT_UNITTEST_ENABLED)
ENDMACRO(SIM_CREATE_QT4_END_JOINTRUNNER)

# - Set up a simple unittest, with name header and source
# SIM_CREATE_QT4_UNITTEST(NAME HEADER SOURCE LIBRARIES...)
#  NAME - the name of the unittest as it will be registred
#  HEADER - Headerfile of the testrunner
#  SOURCE - Sourcefile, with main().
#
# Use together with a header and source for a QtTest unittest, and
# QTEST_MAIN() in the sourcefile, to set up a simple unittest with
# executable name NAME_t(.exe) and testname NAME.
MACRO(SIM_CREATE_QT4_UNITTEST name header source)
  IF(JOINT_UNITTEST_ENABLED)
    SIM_ADD_QT4_JOINT_TEST(${name} ${header} ${source} ${ARGN})
  ELSE(JOINT_UNITTEST_ENABLED)
    QT4_WRAP_CPP(unittest_moc_SRCS ${header})
    SET(runner_NAME ${name})
    SET(link_LIBS ${ARGN}) # Empty, if no extra params

    # Add header as source when generating MSVC projects
    IF(MSVC_IDE)
      ADD_EXECUTABLE(${runner_NAME} ${unittest_moc_SRCS} ${source} ${header})
    ELSE(MSVC_IDE)
      ADD_EXECUTABLE(${runner_NAME} ${unittest_moc_SRCS} ${source})
    ENDIF(MSVC_IDE)

    TARGET_LINK_LIBRARIES(${runner_NAME} ${link_LIBS} ${QT_QTTEST_LIBRARY})
    ADD_TEST(${name} ${runner_NAME})
    set(unittest_moc_SRCS)
  ENDIF(JOINT_UNITTEST_ENABLED)
ENDMACRO(SIM_CREATE_QT4_UNITTEST)

# - Set up a simple unittest, from a base-name
# SIM_CREATE_QT4_UNITTEST2( basename libs...)
#
# Creates a simple unittest with executable name "basename_t(.exe)", testname
# "basename", from the files basename.h and basename.cpp, which must exist,
# QtTest tests, using QTEST_MAIN().
MACRO(SIM_CREATE_QT4_UNITTEST2 name)
    # FIXME: We are not guarranteed that the filename is .cpp - could perhaps
    # check for the other c++ extensions.
    SIM_CREATE_QT4_UNITTEST(${name} ${name}.h ${name}.cpp ${ARGN})
ENDMACRO(SIM_CREATE_QT4_UNITTEST2)

# Creates a plugin from one header and cpp file.
# SIM_CREATE_QT_PLUGIN(targetname ...)
# - targetname is the name of the plugin. There must be a header and a cpp
#   file correspoding to the targetname given.
# - remaining params are libraries that the plugin is to be linked against
MACRO(SIM_CREATE_QT_PLUGIN targetname)
  SET(Source ${targetname}.cpp)
  SET(Header ${targetname}.h)
  SET(LinkLibs ${ARGN})

  SIM_QT4_AUTO_WRAP_CPP(Moc ${Header})
  IF(MSVC_IDE)
    ADD_LIBRARY(${targetname} ${Source} ${Header} ${Moc})
  ELSE(MSVC_IDE)
    ADD_LIBRARY(${targetname} ${Source} ${Moc})
  ENDIF(MSVC_IDE)

  IF(${LinkLibs})
   TARGET_LINK_LIBRARIES(${Library} ${LinkLibs})
  ENDIF(${LinkLibs})
ENDMACRO(SIM_CREATE_QT_PLUGIN)

# Creates a plugin from one header and cpp file and
# creates an optional make install target for the plugin.
#
# SIM_CREATE_QT_PLUGIN(TARGET targetname [SOURCE file1 file2])
#
#  - TARGET            The name of the target (required)
#  - SOURCE            The source files. If not specified, a moc is generated
#                      from ${targetname}.h, and compiled along with ${targetname}.cpp.
MACRO(SIM_CREATE_QT_PLUGIN)
  SIM_VALIDATE_ARGUMENTS(ValidArguments SIM_CREATE_QT_PLUGIN
                         "TARGET"                               # Required
                         "TARGET;SOURCE"                        # Allowed
                         "${ARGV}")
  # Required arguments
  SIM_FETCH_ARGUMENTS(Target TARGET ${ARGV})
  # Optional arguments
  SIM_HAS_ARGUMENT(Source SOURCE ${ARGV})
  SIM_FETCH_ARGUMENTS(Source SOURCE ${ARGV})

  IF(ValidArguments)
    IF(HasSource)
      # Build plugin using custom source files
      ADD_LIBRARY(${Target} SHARED ${Source})
    ELSE(HasSource)
      # Automatic source
      SET(Source ${Target}.cpp)
      SET(Header ${Target}.h)

      SIM_QT4_AUTO_WRAP_CPP(Moc ${Header})

      IF(MSVC_IDE)
        ADD_LIBRARY(${Target} SHARED ${Source} ${Header} ${Moc})
      ELSE(MSVC_IDE)
        ADD_LIBRARY(${Target} SHARED ${Source} ${Moc})
      ENDIF(MSVC_IDE)
    ENDIF(HasSource)
  ENDIF(ValidArguments)
ENDMACRO(SIM_CREATE_QT_PLUGIN)

# Stores the path to Qt in the argument given. Uses
# QT_MOC_EXECUTABLE to extract the path.
# 
# SIM_GET_QT_ROOT(variable)
MACRO(SIM_GET_QT_ROOT variable)
  GET_FILENAME_COMPONENT(${variable} ${QT_MOC_EXECUTABLE} PATH)
  FILE(TO_CMAKE_PATH "${${variable}}/../" ${variable}) 
ENDMACRO(SIM_GET_QT_ROOT)
