# **************************************************************************
AC_INIT(actions/search.cpp.in)
AC_CONFIG_AUX_DIR(cfg)

SIM_AC_MSVC_DSPEX_ENABLE_OPTION

# **************************************************************************
# If the Microsoft Visual C++ cl.exe compiler is available, set us up for
# compiling with it.

SIM_AC_SETUP_MSVCPP_IFELSE

# **************************************************************************

## CPP needed for the Open Inventor version check.
AC_PROG_CPP
## Locate C++ compiler and set C++ as the default compiler to run
## in tests.
AC_PROG_CXX
AC_LANG(C++)

# **************************************************************************
# Miscellaneous options and initializations.

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE(examples, 1.0.0)

# File to cram results from the configure tests into.
AM_CONFIG_HEADER(config.h)

# Turn off default maintainer make-rules -- use ./bootstrap instead.
AM_MAINTAINER_MODE

# **************************************************************************
# Compiler control.

SIM_AC_COMPILE_DEBUG

SIM_AC_DEBUGSYMBOLS
SIM_AC_RTTI_SUPPORT
SIM_AC_EXCEPTION_HANDLING
SIM_AC_PROFILING_SUPPORT
SIM_AC_COMPILER_WARNINGS

AC_ARG_WITH([alternate],
  [AC_HELP_STRING([--with-alternate=keyword], [use keyword-configuration of GUI toolkit])],
  [alternate_option=--alternate=$withval
   sim_ac_alternate_keyword=$withval],
  [alternate_option=])

# **************************************************************************
# For the examples which needs to include gl.h.

AC_CHECK_HEADERS([windows.h])
SIM_AC_CHECK_HEADER_GL(CPPFLAGS="$CPPFLAGS $sim_ac_gl_cppflags")

# **************************************************************************
# Search and set up necessary stuff to use the Inventor implementation.

sim_ac_guiexamples_use_inventor=true
if test x"$with_inventor" = x; then sim_ac_guiexamples_use_inventor=false; fi
if test x"$with_inventor" = xno; then sim_ac_guiexamples_use_inventor=false; fi

if $sim_ac_guiexamples_use_inventor; then
  # If we want to compile and link against InventorXt and Inventor, we
  # need to check for a shitload of libraries.

  SIM_AC_CHECK_MATHLIB
  SIM_AC_CHECK_DL
  SIM_AC_CHECK_X11
  
  if test x"$sim_ac_x11_avail" = xyes; then
    SIM_AC_CHECK_X11SHMEM
    SIM_AC_CHECK_X11MU
    SIM_AC_CHECK_X11XID
    SIM_AC_CHECK_X11_XP
    SIM_AC_CHECK_X_INTRINSIC
  fi
  
  SIM_AC_CHECK_OPENGL([ ], [SIM_AC_ERROR([no-opengl])])

  SIM_AC_CHECK_GLU( , AC_MSG_ERROR(needs the GLU library functions))
  SIM_AC_HAVE_INVENTOR_IFELSE(
    [CPPFLAGS="$sim_ac_inventor_cppflags $CPPFLAGS"
     LDFLAGS="$sim_ac_inventor_ldflags $LDFLAGS"
     LIBS="$sim_ac_inventor_libs $LIBS"],
    AC_MSG_ERROR(couldn't compile and link against Open Inventor))
  SIM_CHECK_MOTIF( , AC_MSG_ERROR(couldn't compile and link with Motif))
  SIM_CHECK_MOTIF_GLWIDGET
  
  SIM_CHECK_XMEDRAWSHADOWS
  
  # If XmeDrawShadows() isn't provided by the installed Motif library,
  # we make our own stub. InventorXt uses this function of Motif, but
  # it wasn't provided in earlier versions of Lesstif (because it's a
  # Motif 2.0 function?).
  
  if test x"$sim_ac_xmedrawshadows_avail" = xno; then
    cat > xmedrawshadows.cpp <<EOF
      extern "C" {
      #include <Xm/Xm.h>
      void XmeDrawShadows(Display *, Drawable, GC, GC, Position, Position, Dimension, Dimension, Dimension, unsigned int) { }
      }
EOF
    $CXX -c $CXXFLAGS $CPPFLAGS xmedrawshadows.cpp
    LIBS="$LIBS `pwd`/xmedrawshadows.o"
  fi
  
  SIM_CHECK_OIV_XT( , AC_MSG_ERROR(couldn't compile and link against the InventorXt library))

  GUI=XT
  Gui=Xt
  gui=xt
  WIDGET=Widget
  EVENT="XAnyEvent *"
  COMPONENTHEADER=

  AM_CONDITIONAL(HAVE_SLIDERSETS, true)
  AM_CONDITIONAL(HAVE_MATERIALEDITOR, true)
  AM_CONDITIONAL(HAVE_DIRECTIONALLIGHTEDITOR, true)
  AM_CONDITIONAL(HAVE_MATERIALLIST, true)
  AM_CONDITIONAL(HAVE_PRINTDIALOG, true)

  SIM_AC_CONFIGURATION_SETTING([GUI toolkit], [SGI InventorXt])

else
  sim_ac_gui_default=soxt

  test x${with_qt+set} = xset && sim_ac_gui_default=soqt
  test x${with_xt+set} = xset && sim_ac_gui_default=soxt
  test x${with_gtk+set} = xset && sim_ac_gui_default=sogtk

  AC_ARG_WITH(
    soxt,
    AC_HELP_STRING([--with-soxt], [build against the SoXt toolkit]),
    [sim_ac_gui_default=soxt])
  AC_ARG_WITH(
    soqt,
    AC_HELP_STRING([--with-soqt], [build against the SoQt toolkit]),
    [sim_ac_gui_default=soqt])
  AC_ARG_WITH(
    sowin,
    AC_HELP_STRING([--with-sowin], [build against the SoWin toolkit]),
    [sim_ac_gui_default=sowin])
  AC_ARG_WITH(
    sogtk,
    AC_HELP_STRING([--with-sogtk], [build against the SoGtk toolkit]),
    [sim_ac_gui_default=sogtk])

  AC_ARG_WITH(
    toolkit,
    AC_HELP_STRING([--with-toolkit=<toolkit>],
                   [select GUI toolkit to use (default=SoXt)]),
    [lwithval=`echo $withval | tr A-Z a-z`
    case $lwithval in
      xt  | soxt)    sim_ac_gui_toolkit=soxt  ;;
      qt  | soqt)    sim_ac_gui_toolkit=soqt  ;;
      win | sowin)   sim_ac_gui_toolkit=sowin ;;
      gtk | sogtk)   sim_ac_gui_toolkit=sogtk ;;
      be  | sobe)    sim_ac_gui_toolkit=sobe  ;;
      *) AC_MSG_ERROR([invalid --with-toolkit value: "$withval"]) ;;
    esac],
    [sim_ac_gui_toolkit=$sim_ac_gui_default])

  SIM_AC_CONFIGURATION_SETTING([GUI toolkit], [$sim_ac_gui_toolkit])

  # **************************************************************************
  # Environment variables to configure the generic sourcefiles.

  sim_ac_path=$PATH
  test x"$prefix" = xNONE || sim_ac_path=$prefix/bin:$sim_ac_path

  sim_ac_gui_configcmd=${sim_ac_gui_toolkit}-config
  AC_PATH_PROG(soguiconfig, $sim_ac_gui_configcmd, false, $sim_ac_path)

  if ! $soguiconfig; then
    SIM_AC_ERROR([unable-to-run-soxx-config])
  fi

  if ! $soguiconfig $alternate_option; then
    AC_MSG_WARN([configuration '$sim_ac_alternate_keyword' not found: fallback on default])
    alternate_option=
  fi

  if test x"$alternate_option" = x""; then
    SIM_AC_CONFIGURATION_SETTING([Configuration setting], [default])
  else
    SIM_AC_CONFIGURATION_SETTING([Configuration setting], [$sim_ac_alternate_keyword])
  fi

  GUI=`$soguiconfig $alternate_option --ac-subst GUI`
  Gui=`$soguiconfig $alternate_option --ac-subst Gui`
  gui=`$soguiconfig $alternate_option --ac-subst gui`
  WIDGET=`$soguiconfig $alternate_option --ac-subst WIDGET`
  EVENT=`$soguiconfig $alternate_option --ac-subst EVENT`
  COMPONENTHEADER=`$soguiconfig $alternate_option --ac-subst COMPONENTHEADER`


  # Which component examples to build.

  AM_CONDITIONAL(HAVE_SLIDERSETS, false)
  AM_CONDITIONAL(HAVE_MATERIALEDITOR, false)
  AM_CONDITIONAL(HAVE_DIRECTIONALLIGHTEDITOR, false)
  AM_CONDITIONAL(HAVE_MATERIALLIST, false)
  AM_CONDITIONAL(HAVE_PRINTDIALOG, false)

  CPPFLAGS="$CPPFLAGS `$soguiconfig $alternate_option --cppflags`"
  CXXFLAGS="$CXXFLAGS `$soguiconfig $alternate_option --cxxflags`"
  LDFLAGS="$LDFLAGS `$soguiconfig $alternate_option --ldflags`"
  LIBS="`$soguiconfig $alternate_option --libs` $LIBS"

  AC_MSG_CHECKING([basic So$Gui linking])
  AC_TRY_LINK([#include <Inventor/$Gui/So$Gui.h>],
              [(void)So$Gui::init((const char *)NULL);],
              [AC_MSG_RESULT(ok)],
              [AC_MSG_RESULT(failed!)
               AC_MSG_ERROR([Failed to link a simple test program -- see config.log for error information.])]
             );
fi

AC_SUBST(GUI)
AC_SUBST(Gui)
AC_SUBST(gui)
AC_SUBST(EVENT)
AC_SUBST(WIDGET)
AC_SUBST(COMPONENTHEADER)


# **************************************************************************
# Inventor feature checking.

## FIXME: what is the point of setting up C here before C++? Strange.
## 20010919 mortene.
AC_LANG(C)
AC_LANG(C++)

# Check for the availability of these nodes, which is not part
# of older Inventor implementations.
SIM_AC_HAVE_INVENTOR_NODE(SoPolygonOffset)
SIM_AC_HAVE_INVENTOR_NODE(SoMarkerSet)
SIM_AC_HAVE_INVENTOR_NODE(SoImage)
SIM_AC_HAVE_INVENTOR_NODE(SoTextureScalePolicy)
SIM_AC_HAVE_INVENTOR_NODE(SoTextureUnit)
SIM_AC_HAVE_INVENTOR_NODE(SoExtSelection, [
  SIM_AC_HAVE_INVENTOR_FEATURE(
    [for SoExtSelection::lassoMode],
    [#include <Inventor/nodes/SoExtSelection.h>], [
     SoExtSelection * sel = new SoExtSelection;
     sel->lassoMode = SoExtSelection::VISIBLE_SHAPES; ],
    [HAVE_SOEXTSELECTION_LASSOMODE])
  ])

SIM_AC_HAVE_INVENTOR_FEATURE(
  [for SoGLRenderAction::SORTED_OBJECT_SORTED_TRIANGLE_BLEND],
  [#include <Inventor/actions/SoGLRenderAction.h>], [
   int i = SoGLRenderAction::SORTED_OBJECT_SORTED_TRIANGLE_BLEND;],
  [HAVE_SOGLRENDERACTION_SORTED_OBJECT_SORTED_TRIANGLE_BLEND])

SIM_AC_HAVE_INVENTOR_FEATURE(
  [for So${Gui}Component::setFullScreen()],
  [#include <Inventor/${Gui}/viewers/So${Gui}ExaminerViewer.h>], [
   So${Gui}ExaminerViewer * viewer = (So${Gui}ExaminerViewer *) 0;
   viewer->setFullScreen(FALSE);],
  [HAVE_SOCOMPONENT_SETFULLSCREEN])

SIM_AC_HAVE_INVENTOR_FEATURE(
  [for So${Gui}Viewer::setStereoViewing()],
  [#include <Inventor/${Gui}/viewers/So${Gui}ExaminerViewer.h>], [
   So${Gui}ExaminerViewer * viewer = (So${Gui}ExaminerViewer *) 0;
   viewer->setStereoViewing(FALSE);],
  [HAVE_VIEWER_STEREO_VIEWING])

SIM_AC_HAVE_INVENTOR_FEATURE(
  [for So${Gui}Viewer::setQuadBufferStereo()],
  [#include <Inventor/${Gui}/viewers/So${Gui}ExaminerViewer.h>], [
   So${Gui}ExaminerViewer * viewer = (So${Gui}ExaminerViewer *) 0;
   viewer->setQuadBufferStereo(0);],
  [HAVE_VIEWER_QUADBUFFER_STEREO])

SIM_AC_HAVE_INVENTOR_FEATURE(
  [for So${Gui}GLWidget::setAccumulationBuffer()],
  [#include <Inventor/${Gui}/So${Gui}RenderArea.h>], [
   So${Gui}RenderArea * viewer = (So${Gui}RenderArea *) 0;
   viewer->setAccumulationBuffer(FALSE);],
  [HAVE_SOGUIGLWIDGET_ACCUMULATIONBUFFER])

SIM_AC_HAVE_INVENTOR_FEATURE(
  [for SoIntersectionDetectionAction class],
  [#include <Inventor/collision/SoIntersectionDetectionAction.h>], [
   SoIntersectionDetectionAction ida;
   ida.setDraggersEnabled(FALSE);],
  [HAVE_SOINTERSECTIONDETECTIONACTION])

SIM_AC_HAVE_INVENTOR_FEATURE(
  [for Open Inventor HardCopy support],
  [#include <HardCopy/SoHardCopy.h>], [
   const char * v = SoHardCopy::getVersion();],
  [HAVE_HARDCOPY])

# **************************************************************************
# Use SmallChange if available.

SIM_AC_HAVE_SMALLCHANGE_IFELSE([
  CPPFLAGS="$CPPFLAGS `$sim_ac_smallchange_configcmd $alternate_option --cppflags`"
  CXXFLAGS="$CXXFLAGS `$sim_ac_smallchange_configcmd $alternate_option --cxxflags`"
  CFLAGS="$CFLAGS `$sim_ac_smallchange_configcmd $alternate_option --cflags`"
  LDFLAGS="$LDFLAGS `$sim_ac_smallchange_configcmd $alternate_option --ldflags`"
  LIBS="`$sim_ac_smallchange_configcmd $alternate_option --libs` $LIBS"
  AC_DEFINE(HAVE_SMALLCHANGE_LIBRARY, 1, [Define to enable use of SmallChange library])
  SIM_AC_CONFIGURATION_SETTING([SmallChange], [is being used])
], [
  if $sim_ac_smallchange_desired; then
    SIM_AC_ERROR([smallchange-unavailable])
  else
    SIM_AC_CONFIGURATION_SETTING([SmallChange], [not used (enable with --with-smallchange)])
  fi
])

# **************************************************************************
# If we're using SoQt, check to see if SimVoleon is also available.
# Those are the two dependencies of the examples under the
# volumerendering/ directory.

# Default to not look for SimVoleon, as we'll get lots of warnings
# from configure in the common case that it is _not_ available.
sim_ac_simvoleon_desired=false

if test x"$sim_ac_gui_toolkit" = x"soqt"; then

  SIM_AC_QT_PROG(MOC, moc)
  if test x"$MOC" = x"false"; then
    SIM_AC_ERROR([no-moc])
  fi

  SIM_AC_QT_PROG(UIC, uic)
  if test x"$UIC" = x"false"; then
    SIM_AC_ERROR([no-uic])
  fi

  SIM_AC_HAVE_SIMVOLEON_IFELSE([
    CPPFLAGS="$sim_ac_simvoleon_cppflags $CPPFLAGS"
    CFLAGS="$sim_ac_simvoleon_cflags $CFLAGS"
    CXXFLAGS="$sim_ac_simvoleon_cxxflags $CXXFLAGS"
    LDFLAGS="$sim_ac_simvoleon_ldflags $LDFLAGS"
    LIBS="$sim_ac_simvoleon_libs $LIBS"

    SIM_AC_CONFIGURATION_SETTING([SimVoleon], [is being used])
    AC_DEFINE(HAVE_SIMVOLEON_LIBRARY, 1, [Define to enable use of SimVoleon library])
  ], [
  if $sim_ac_simvoleon_desired; then
    SIM_AC_ERROR([simvoleon-unavailable])
  else
    SIM_AC_CONFIGURATION_SETTING([SimVoleon], [not used (enable with --with-simvoleon)])
  fi
  ])
else
  SIM_AC_CONFIGURATION_SETTING([SimVoleon], [not used (examples only works with SoQt)])
fi

AM_CONDITIONAL(HAVE_SIMVOLEON, $sim_ac_simvoleon_avail)

# **************************************************************************
# At least one of the SimVoleon examples needs simage. Will just do a
# general check for it, in case other examples pops up which uses it.

SIM_AC_HAVE_SIMAGE_IFELSE([
  CPPFLAGS="$sim_ac_simage_cppflags $CPPFLAGS"
  LDFLAGS="$sim_ac_simage_ldflags $LDFLAGS"
  LIBS="$sim_ac_simage_libs $LIBS"
  SIM_AC_CONFIGURATION_SETTING([simage], [is being used])
  AC_DEFINE(HAVE_SIMAGE_LIBRARY, 1, [Define to enable explicit use of simage library])
],
[
  SIM_AC_CONFIGURATION_SETTING([simage], [not found (some example programs will not be built)])
])

AM_CONDITIONAL(HAVE_SIMAGE, $sim_ac_simvoleon_avail)

# **************************************************************************
# Remove redundant options from certain option lists, to clean up the
# compiler and linker invocations.

SIM_AC_UNIQIFY_LIST(CPPFLAGS, $CPPFLAGS)
SIM_AC_UNIQIFY_LIST(CXXFLAGS, $CXXFLAGS)
SIM_AC_UNIQIFY_LIST(CFLAGS, $CFLAGS)
SIM_AC_UNIQIFY_LIST(LDFLAGS, $LDFLAGS)
SIM_AC_UNIQIFY_LIST(LIBS, $LIBS)

# **************************************************************************
# Support for generating VisualStudio project files

soguiexamples_src_dir=`cd "$srcdir"; pwd`
soguiexamples_build_dir=`pwd`
AC_SUBST([soguiexamples_src_dir])
AC_SUBST([soguiexamples_build_dir])

if $sim_ac_make_dspex; then
  soguiexamples_subst="\\\$\$\\(COIN3DDIR\\)=`cygpath -u $COIN3DDIR`"
  SIM_AC_MSVC_DSPEX_SETUP([So${Gui}Examples], [$soguiexamples_src_dir], 
                          [vc6], [$soguiexamples_subst])
  SIM_AC_MSVC_DSPEX_PREPARE([$soguiexamples_src_dir], 
                            [$soguiexamples_build_dir])
fi


# **************************************************************************
# All files configure must automatically generate.

AC_OUTPUT([
	Makefile

	components/Makefile
	components/SoGuiSnapshotViewer.cpp
	components/SoGuiSnapshotViewer.h
	components/backgroundimg.cpp
	components/computils.cpp
	components/computils.h
	components/examinerviewer.cpp
	components/flyviewer.cpp
	components/grapheditor.cpp
	components/lightsliderset.cpp
	components/materiallist.cpp
	components/materiallist2.cpp
	components/materialsliderset.cpp
	components/materialsliderset2.cpp
	components/overlay.cpp
	components/planeviewer.cpp
	components/renderarea.cpp
	components/roster.cpp
	components/snapshotviewer.cpp
	components/spaceballdemo.cpp 
	components/transformsliderset.cpp

	actions/Makefile
	actions/search.cpp
	actions/raypick.cpp
	actions/intersection.cpp

	annex/Makefile
        annex/hardcopy.cpp

	draggers/Makefile
	draggers/translate1.cpp
	draggers/translate2.cpp
	draggers/dragpoint.cpp

	engines/Makefile
	engines/computebbox.cpp
	engines/computexfbbox.cpp

	eyecandy/Makefile
	eyecandy/moirepatterns.cpp
	eyecandy/juliaanim.cpp
	eyecandy/mandelzoom.cpp
	eyecandy/blob.cpp
	eyecandy/simbuoy.cpp

	manipulators/Makefile
	manipulators/pointlightmanip.cpp
	manipulators/tabboxmanip.cpp

	nodekits/Makefile
	nodekits/scalemarker.cpp
	nodekits/wavekitdemo.cpp

	nodes/Makefile
	nodes/drawstyle.cpp
	nodes/material.cpp
	nodes/selection.cpp
	nodes/slideshow.cpp
	nodes/sphere.cpp
	nodes/spherecolor.cpp
	nodes/rotation.cpp
	nodes/scale.cpp
	nodes/translation.cpp
	nodes/transform.cpp
	nodes/rotor.cpp
	nodes/directionallight.cpp
	nodes/pointlight.cpp
	nodes/spotlight.cpp
	nodes/lights.cpp
	nodes/faceset.cpp
	nodes/facesetindexed.cpp
	nodes/quadmesh.cpp
	nodes/trianglestripset.cpp
	nodes/camera.cpp
	nodes/blinker.cpp
	nodes/texture.cpp
	nodes/texture3.cpp
	nodes/environment.cpp
	nodes/atmospheric.cpp
	nodes/shuttle.cpp
	nodes/complexity.cpp
	nodes/text2.cpp
	nodes/text3.cpp
	nodes/clipplane.cpp
	nodes/levelofdetail.cpp
	nodes/extselection.cpp
	nodes/pointset.cpp
	nodes/markerset.cpp
	nodes/image.cpp
	nodes/bigimage.cpp
	nodes/textureunit.cpp

	sensors/Makefile
	sensors/timersensor.cpp

	volumerendering/Makefile
	volumerendering/readvol.cpp
	volumerendering/changingdataset.cpp
	volumerendering/examine.cpp
	volumerendering/orthoslicer.cpp
	volumerendering/raypick.cpp
	volumerendering/rgbload.cpp
	volumerendering/simple8bit.cpp

	coin-competitions/Makefile

	coin-competitions/SIM-20010803/Makefile
	coin-competitions/SIM-20010803/chart.cpp
	coin-competitions/SIM-20010803/plasmafun.cpp
	coin-competitions/SIM-20010803/stars.cpp

	coin-competitions/SIM-20010824/Makefile
	coin-competitions/SIM-20010824/smiley.cpp
	coin-competitions/SIM-20010824/plasmaball.cpp
	coin-competitions/SIM-20010824/styx.cpp
	coin-competitions/SIM-20010824/stars2.cpp

	coin-competitions/SIM-20010914/Makefile
	coin-competitions/SIM-20010914/Moolah.cpp
	coin-competitions/SIM-20010914/calculator.cpp
	coin-competitions/SIM-20010914/coinhistory.cpp
	coin-competitions/SIM-20010914/kaos.cpp
	coin-competitions/SIM-20010914/rec.cpp

	coin-competitions/SIM-20011005/Makefile
	coin-competitions/SIM-20011005/lorenz.cpp
	coin-competitions/SIM-20011005/nurbscurve.cpp
	coin-competitions/SIM-20011005/cubes.cpp

	coin-competitions/SIM-20011116/Makefile
	coin-competitions/SIM-20011116/25bc5bb.cpp
	coin-competitions/SIM-20011116/foo.cpp
	coin-competitions/SIM-20011116/shaker.cpp

	coin-competitions/SIM-20020118/Makefile
	coin-competitions/SIM-20020118/blocks.cpp

	coin-competitions/SIM-20020503/Makefile
	coin-competitions/SIM-20020503/ballinthehoop.cpp
	coin-competitions/SIM-20020503/flow.cpp
	coin-competitions/SIM-20020503/typeomatic.cpp
])

SIM_AC_CONFIGURATION_SUMMARY

echo ""
echo "Now run 'make' to build the examples."
echo ""
echo "(Note that they are not installed, so after building you should"
echo "execute them straight from this directory's subdirectories.)"
echo ""

# **************************************************************************
