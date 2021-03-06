# **************************************************************************
AC_INIT(actions/search.cpp.in)
AC_CONFIG_AUX_DIR(cfg)

SIM_AC_SETUP_MKS

SIM_AC_MSVC_DSPEX_ENABLE_OPTION

# **************************************************************************
# If the Microsoft Visual C++ cl.exe compiler is available, set us up for
# compiling with it.

SIM_AC_SETUP_MSVCPP_IFELSE
AM_CONDITIONAL(BUILD_WITH_MSVC, $BUILD_WITH_MSVC)

# **************************************************************************

# cross_compiling: On MKS, configure will open a window when trying to run
# the executable a.out in the cross-compilation test because it is not
# named *.exe, halting the configure script until it has been closed, even
# resulting in a faulty conclusion for the test (cross_compiling=yes).
# By setting the $cross_compiling variable to yes in advance, this test is
# skipped.  We are of course not cross-compiling, so we correct the variable
# afterwards.  2003-06-25 larsa

case $build in
*-mks ) cross_compiling=yes ;;
esac

AC_PROG_CC

case $build in
*-mks ) cross_compiling=yes ;;
esac

# **************************************************************************

## CPP needed for the Open Inventor version check.
AC_PROG_CPP
## Locate C++ compiler and set C++ as the default compiler to run
## in tests.
AC_PROG_CXX
AC_PROG_CXXCPP

SIM_AC_STRIP_EXIT_DECLARATION

AC_LANG(C++)

# **************************************************************************
# Miscellaneous options and initializations.

AC_CANONICAL_SYSTEM

# **************************************************************************
# Universal Binary support (Mac OS X)

SIM_AC_UNIVERSAL_BINARIES

AM_INIT_AUTOMAKE(examples, 1.0.0)

# File to cram results from the configure tests into.
AM_CONFIG_HEADER(config.h)

# Turn off default maintainer make-rules -- use ./bootstrap instead.
AM_MAINTAINER_MODE

# volumerendering/Cute/Cute.a needs this:
AC_PROG_RANLIB

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

# These needs to be called so the "--with-*" options have an effect.
SIM_AC_WITH_INVENTOR
SIM_AC_WITH_INVENTORXT
SIM_AC_WITH_INVENTORQT

if $sim_ac_want_inventor; then
  # If we want to compile and link against Inventor, we
  # need to check for these libraries.

  SIM_AC_CHECK_MATHLIB
  SIM_AC_CHECK_DL

  # Either InventorXt or InventorQt, not both
  if $sim_ac_want_inventorqt; then
    sim_ac_want_inventorxt=false
  else # ..nor neither
    if $sim_ac_want_inventorxt; then :; else
      AC_MSG_ERROR(Either InventorXt or InventorQt must be used along with SGI/TGS Inventor.)
    fi
  fi

  # InventorXt (SGI or TGS) needs a heap of libs
  if $sim_ac_want_inventorxt; then
    SIM_AC_CHECK_X11
    if test x"$sim_ac_x11_avail" = xno; then
      AC_MSG_ERROR(Could not compile or link against X11 libraries.)
    fi
    SIM_AC_CHECK_X11SHMEM
    SIM_AC_CHECK_X11MU
    SIM_AC_CHECK_X11XID
    SIM_AC_CHECK_X11_XP
    SIM_AC_CHECK_X_INTRINSIC
  fi

  # InventorQt (SGI or TGS) needs a heap of libs
  if $sim_ac_want_inventorqt; then
    SIM_AC_CHECK_QT([
      CPPFLAGS="$CPPFLAGS $sim_ac_qt_cppflags"
      LDFLAGS="$LDFLAGS $sim_ac_qt_ldflags"
      LIBS="$sim_ac_qt_libs $LIBS"
    ], [
      SIM_AC_ERROR([no-qt])
    ])
  
    SIM_AC_CHECK_QGL([
      CPPFLAGS="$CPPFLAGS $sim_ac_qgl_cppflags"
      LDFLAGS="$LDFLAGS $sim_ac_qgl_ldflags"
      LIBS="$sim_ac_qgl_libs $LIBS"
    ], [
      SIM_AC_ERROR([no-qgl])
    ])
  fi
  
  SIM_AC_CHECK_OPENGL([ ], [SIM_AC_ERROR([no-opengl])])

  SIM_AC_CHECK_GLU( , AC_MSG_ERROR(needs the GLU library functions))
  SIM_AC_HAVE_INVENTOR_IFELSE(
    [CPPFLAGS="$sim_ac_inventor_cppflags $CPPFLAGS"
     LDFLAGS="$sim_ac_inventor_ldflags $LDFLAGS"
     LIBS="$sim_ac_inventor_libs $LIBS"],
    AC_MSG_ERROR(couldn't compile and link against Open Inventor))

  AM_CONDITIONAL(HAVE_SLIDERSETS, true)
  AM_CONDITIONAL(HAVE_MATERIALEDITOR, true)
  AM_CONDITIONAL(HAVE_DIRECTIONALLIGHTEDITOR, true)
  AM_CONDITIONAL(HAVE_MATERIALLIST, true)
  AM_CONDITIONAL(HAVE_PRINTDIALOG, true)

  if $sim_ac_want_inventorxt; then
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

    SIM_AC_CONFIGURATION_SETTING([GUI toolkit], [InventorXt])
  fi

  if $sim_ac_want_inventorqt; then
    SIM_CHECK_OIV_QT( , AC_MSG_ERROR(couldn't compile and link against the InventorQt library))

    GUI=QT
    Gui=Qt
    gui=qt
    WIDGET="QWidget *"
    EVENT="QEvent *"
    COMPONENTHEADER="Q_OBJECT"

    SIM_AC_CONFIGURATION_SETTING([GUI toolkit], [InventorQt])
    sim_ac_gui_toolkit=inventorqt
    # We'd rather not see all those ugly g++ warnings from the SGI / TGS 
    # headers.
    if test x"$GXX" = x"yes"; then
      CXXFLAGS="$CXXFLAGS -w"
    fi
  fi

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
SIM_AC_HAVE_INVENTOR_NODE(SoBumpMap)
SIM_AC_HAVE_INVENTOR_NODE(SoBumpMapTransform)
SIM_AC_HAVE_INVENTOR_NODE(SoSceneTexture2)
SIM_AC_HAVE_INVENTOR_NODE(SoExtSelection, [
  SIM_AC_HAVE_INVENTOR_FEATURE(
    [for SoExtSelection::lassoMode],
    [#include <Inventor/nodes/SoExtSelection.h>], [
     SoExtSelection * sel = new SoExtSelection;
     sel->lassoMode = SoExtSelection::VISIBLE_SHAPES; ],
    [HAVE_SOEXTSELECTION_LASSOMODE])
  ])
SIM_AC_HAVE_INVENTOR_NODE(SoShaderProgram)
SIM_AC_HAVE_INVENTOR_NODE(SoFragmentShader)
SIM_AC_HAVE_INVENTOR_NODE(SoVertexShader)

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

sim_ac_smallchange_desired=false

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

AM_CONDITIONAL(HAVE_SMALLCHANGE, $sim_ac_smallchange_avail)

# **************************************************************************
# Use SIM Aruba if available.

sim_ac_simaruba_desired=false

SIM_AC_HAVE_SIMARUBA_IFELSE([
  CPPFLAGS="$CPPFLAGS `$sim_ac_simaruba_configcmd $alternate_option --cppflags`"
  CXXFLAGS="$CXXFLAGS `$sim_ac_simaruba_configcmd $alternate_option --cxxflags`"
  CFLAGS="$CFLAGS `$sim_ac_simaruba_configcmd $alternate_option --cflags`"
  LDFLAGS="$LDFLAGS `$sim_ac_simaruba_configcmd $alternate_option --ldflags`"
  LIBS="`$sim_ac_simaruba_configcmd $alternate_option --libs` $LIBS"
  AC_DEFINE(HAVE_SIMARUBA_LIBRARY, 1, [Define to enable use of SIM Aruba library])
  SIM_AC_CONFIGURATION_SETTING([SIM Aruba], [is being used])
], [
  if $sim_ac_simaruba_desired; then
    SIM_AC_ERROR([simaruba-unavailable])
  else
    SIM_AC_CONFIGURATION_SETTING([SIM Aruba], [not used (enable with --with-simaruba)])
  fi
])

AM_CONDITIONAL(HAVE_SIMARUBA, $sim_ac_simaruba_avail)

# **************************************************************************
# Use libcoinscenery if available.

sim_ac_coinscenery_desired=false

SIM_AC_HAVE_COINSCENERY_IFELSE([
  CPPFLAGS="$CPPFLAGS `$sim_ac_coinscenery_configcmd $alternate_option --cppflags`"
  CXXFLAGS="$CXXFLAGS `$sim_ac_coinscenery_configcmd $alternate_option --cxxflags`"
  CFLAGS="$CFLAGS `$sim_ac_coinscenery_configcmd $alternate_option --cflags`"
  LDFLAGS="$LDFLAGS `$sim_ac_coinscenery_configcmd $alternate_option --ldflags`"
  LIBS="`$sim_ac_coinscenery_configcmd $alternate_option --libs` $LIBS"
  AC_DEFINE(HAVE_COINSCENERY_LIBRARY, 1, [Define to enable use of libcoinscenery binding nodes])
  SIM_AC_CONFIGURATION_SETTING([libcoinscenery], [is being used])
], [
  if $sim_ac_coinscenery_desired; then
    AC_MSG_ERROR([Couldn't link with libcoinscenery.])
  else
    SIM_AC_CONFIGURATION_SETTING([libcoinscenery], [not used (enable with --with-coinscenery)])
  fi
])

AM_CONDITIONAL(HAVE_COINSCENERY, $sim_ac_coinscenery_avail)

# **************************************************************************
# Some particular tests are needed if Qt is the GUI toolkit.

sim_ac_using_qt=false
if test x"$sim_ac_gui_toolkit" = x"soqt"; then sim_ac_using_qt=true; fi
if test x"$sim_ac_gui_toolkit" = x"inventorqt"; then sim_ac_using_qt=true; fi

sim_ac_using_qt_4=false

if $sim_ac_using_qt; then
  SIM_AC_QT_PROG(MOC, moc)
  if test x"$MOC" = x"false"; then
    SIM_AC_ERROR([no-moc])
  fi

  SIM_AC_QT_VERSION
  if test "$sim_ac_qt_major_version" = "4"; then
    SIM_AC_QT_PROG(UIC, uic3)
    if test x"$UIC" = x"false"; then
      SIM_AC_ERROR([no-uic3])
    fi
    sim_ac_using_qt_4=true
  else
    SIM_AC_QT_PROG(UIC, uic)
    if test x"$UIC" = x"false"; then
      SIM_AC_ERROR([no-uic])
    fi
  fi
fi

AM_CONDITIONAL(USING_QT_4, $sim_ac_using_qt_4)

# **************************************************************************
# If we're using SoQt, check to see if SIM Voleon is also available.
# Those are the two dependencies of the examples under the
# volumerendering/ directory.

sim_ac_simvoleon_avail=false
if test x"$sim_ac_gui_toolkit" = x"soqt"; then
# Default to not look for SIM Voleon, as we'll get lots of warnings
# from configure in the common case that it is _not_ available.
sim_ac_simvoleon_desired=false

  SIM_AC_HAVE_SIMVOLEON_IFELSE([
    CPPFLAGS="$sim_ac_simvoleon_cppflags $CPPFLAGS"
    CFLAGS="$sim_ac_simvoleon_cflags $CFLAGS"
    CXXFLAGS="$sim_ac_simvoleon_cxxflags $CXXFLAGS"
    LDFLAGS="$sim_ac_simvoleon_ldflags $LDFLAGS"
    LIBS="$sim_ac_simvoleon_libs $LIBS"

    SIM_AC_CONFIGURATION_SETTING([SIM Voleon], [is being used])
    AC_DEFINE(HAVE_SIMVOLEON_LIBRARY, 1, [Define to enable use of SIM Voleon library])

    # SIM Qt extension widgets needed for volumerendering examples.
    if test -d $srcdir/volumerendering/Cute; then
      :
    else
      AC_MSG_ERROR([Detected old CVS checkout of SoGuiExamples, exiting. To fix, 'cd' to the SoGuiExamples/volumerendering/ directory, do a 'cvs co Cute' and re-run configure.])
    fi

    # Check if Qt4 has been compiled with Qt3Support
    if $sim_ac_using_qt_4; then
      sim_ac_save_libs=$LIBS
      LIBS="-lQt3Support $LIBS"
      AC_MSG_CHECKING(if Qt4 has Qt3Support enabled)
      AC_LANG_PUSH(C++)
      AC_TRY_LINK(
        [#include <Qt3Support/q3valuelist.h>],
        [Q3ValueList<float> params;],
        [sim_ac_qt3support_avail=true],
        [sim_ac_qt3support_avail=false])
      AC_LANG_POP
      AC_MSG_RESULT($sim_ac_qt3support_avail)
    
      if $sim_ac_qt3support_avail; then
        SIM_AC_CONFIGURATION_SETTING([Qt3Support], [found enabled in Qt4 and is being used])
        AC_DEFINE(HAVE_QT3SUPPORT_LIBRARY, 1, [Define to enable use of Qt3Support library])
        # **************************************************************************
      else
        SIM_AC_CONFIGURATION_SETTING([Qt3Support], [is not being enabled in Qt4 used -- SIM Voleon examples not built])
        LIBS=$sim_ac_save_libs
        AC_DEFINE(HAVE_QT3SUPPORT_LIBRARY, 0, [Define to enable use of Qt3Support library])
      fi    
    fi
  ], [
    if $sim_ac_simvoleon_desired; then
      SIM_AC_ERROR([simvoleon-unavailable])
    else
      SIM_AC_CONFIGURATION_SETTING([SIM Voleon], [not used (enable with --with-simvoleon)])
    fi
  ])
else
  if $sim_ac_want_inventor; then
    :  # don't warn if we're using SGI or TGS Inventor, as SIM Voleon is an obvious no-go then
  else
    SIM_AC_CONFIGURATION_SETTING([SIM Voleon], [not used (examples only works with SoQt)])
  fi
fi

if test x"$sim_ac_gui_toolkit" = x"soqt"; then
  sim_ac_use_soqt=true
else
  sim_ac_use_soqt=false
fi  
AM_CONDITIONAL(HAVE_SIMVOLEON, $sim_ac_simvoleon_avail)
AM_CONDITIONAL(HAVE_QT3SUPPORT_LIBRARY, $sim_ac_qt3support_avail)
AM_CONDITIONAL(USE_SOQT, $sim_ac_use_soqt && $sim_ac_qt3support_avail)

# **************************************************************************
# If we're using Inventor and InventorQt, check to see if VolumeViz is
# also available. Those are the two alternate dependencies of the examples
# under the volumerendering/ directory.

sim_ac_volumeviz_avail=false
if test x"$sim_ac_gui_toolkit" = x"inventorqt"; then

  sim_ac_save_libs=$LIBS
  LIBS="-lInventorVR $LIBS"
  AC_MSG_CHECKING(for TGS VolumeViz)
  AC_LANG_PUSH(C++)
  AC_TRY_LINK(
    [#include <VolumeViz/nodes/SoVolumeRendering.h>],
    [SoVolumeRendering::init();],
    [sim_ac_volumeviz_avail=true],
    [sim_ac_volumeviz_avail=false])
  AC_LANG_POP
  AC_MSG_RESULT($sim_ac_volumeviz_avail)

  if $sim_ac_volumeviz_avail; then
    SIM_AC_CONFIGURATION_SETTING([TGS VolumeViz], [is being used])
    AC_DEFINE(HAVE_VOLUMEVIZ_LIBRARY, 1, [Define to enable use of TGS VolumeViz library])
  else
    SIM_AC_CONFIGURATION_SETTING([TGS VolumeViz], [is not being used -- failed to build])
    LIBS=$sim_ac_save_libs
  fi

  # SIM Qt extension widgets needed for volumerendering examples.
  if test -d $srcdir/volumerendering/Cute; then
    :
  else
    AC_MSG_ERROR([Detected old CVS checkout of SoGuiExamples, exiting. To fix, 'cd' to the SoGuiExamples/volumerendering/ directory, do a 'cvs co Cute' and re-run configure.])
  fi
fi

AM_CONDITIONAL(HAVE_VOLUMEVIZ, $sim_ac_volumeviz_avail)

# **************************************************************************
# If we're using a non-SIM Inventor, check to see if MeshViz is
# also available.

sim_ac_meshviz_avail=false
if $sim_ac_want_inventor; then
  sim_ac_save_libs=$LIBS
  LIBS="-lMeshViz $LIBS"
  AC_MSG_CHECKING(for TGS MeshViz)
  AC_LANG_PUSH(C++)
  AC_TRY_LINK(
    [#include <DataViz/PoDataViz.h>],
    [PoDataViz::init();],
    [sim_ac_meshviz_avail=true],
    [sim_ac_meshviz_avail=false])
  AC_LANG_POP
  AC_MSG_RESULT($sim_ac_meshviz_avail)

  if $sim_ac_meshviz_avail; then
    SIM_AC_CONFIGURATION_SETTING([TGS MeshViz], [is being used])
    AC_DEFINE(HAVE_MESHVIZ_LIBRARY, 1, [Define to enable use of TGS MeshViz library])
  else
    SIM_AC_CONFIGURATION_SETTING([TGS MeshViz], [is not being used -- failed to build])
    LIBS=$sim_ac_save_libs
  fi
fi

AM_CONDITIONAL(HAVE_MESHVIZ, $sim_ac_meshviz_avail)

# **************************************************************************
# At least one of the SIM Voleon examples needs simage. Will just do a
# general check for it, in case other examples pops up which uses it.

if $sim_ac_want_inventor; then
  AM_CONDITIONAL(HAVE_SIMAGE, false)
else
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
  AM_CONDITIONAL(HAVE_SIMAGE, $sim_ac_simage_avail)
fi

# **************************************************************************
# Remove redundant options from certain option lists, to clean up the
# compiler and linker invocations.

SIM_AC_UNIQIFY_OPTION_LIST(CPPFLAGS, $CPPFLAGS)
SIM_AC_UNIQIFY_OPTION_LIST(CXXFLAGS, $CXXFLAGS)
SIM_AC_UNIQIFY_OPTION_LIST(CFLAGS, $CFLAGS)
SIM_AC_UNIQIFY_OPTION_LIST(LDFLAGS, $LDFLAGS)
SIM_AC_UNIQIFY_OPTION_LIST(LIBS, $LIBS)

# **************************************************************************
# Support for generating VisualStudio project files

soguiexamples_src_dir=`cd "$srcdir"; pwd`
soguiexamples_build_dir=`pwd`
AC_SUBST([soguiexamples_src_dir])
AC_SUBST([soguiexamples_build_dir])

if $sim_ac_make_dspex; then
  if test x"$COIN3DDIR" = x""; then
    soguiexamples_subst=
  else
    soguiexamples_subst="\\\$\$\\(COIN3DDIR\\)=`cygpath -u $COIN3DDIR`"
  fi
  SIM_AC_MSVC_DSPEX_SETUP([So${Gui}Examples], [$soguiexamples_src_dir],
                          [$soguiexamples_build_dir],
                          [vc6], [$soguiexamples_subst], [-DHAVE_CONFIG_H])
  SIM_AC_MSVC_DSPEX_PREPARE([$soguiexamples_src_dir], 
                            [$soguiexamples_build_dir])
fi


# **************************************************************************
# All files configure must automatically generate.

AC_CONFIG_FILES(
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
        components/multifileviewer.cpp
        components/overlay.cpp
        components/planeviewer.cpp
        components/renderarea.cpp
        components/simplerenderarea.cpp
        components/simpleexviewer.cpp
        components/roster.cpp
        components/snapshotviewer.cpp
        components/transformsliderset.cpp

        actions/Makefile
        actions/search.cpp
        actions/raypick.cpp
        actions/intersection.cpp

        annex/Makefile
        annex/hardcopy.cpp

        draggers/Makefile
        draggers/jackdragger.cpp
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
        eyecandy/toonshader.cpp

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
        nodes/bumpmap.cpp
        nodes/scenetexture.cpp
        nodes/nurbssurface.cpp

        sensors/Makefile
        sensors/timersensor.cpp

        sound/Makefile
        sound/audiocallback.cpp
        sound/manysources.cpp

        volumerendering/Makefile
        volumerendering/Cute/Makefile
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
)

# MKS will have "\c" as $ECHO_C, but that string in the config.status
# substitution command will cause config.status to hang because it is
# somehow translated to "&c".  We therefore blank it here, and restore
# it further below, after AC_OUTPUT.

sim_ac_ECHO_C=$ECHO_C
case $build in
*-mks ) ECHO_C="" ;;
esac

AC_OUTPUT

ECHO_C=$sim_ac_ECHO_C

# *******************************************************************

SIM_AC_CONFIGURATION_SUMMARY

echo ""
echo "Now run 'make' to build the examples."
case $target_os in
  darwin* ) 
    echo "Run 'make app-bundles' to create Mac OS X application bundles." ;; 
esac
echo ""

echo "(Note that they are not installed, so after building you should"
echo "execute them straight from this directory's subdirectories.)"
echo ""

# **************************************************************************
