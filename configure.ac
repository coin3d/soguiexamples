# **************************************************************************
AC_INIT(actions/search.cpp.in)
AC_CONFIG_AUX_DIR(cfg)

# **************************************************************************
# Check the CVS repository setup

SIM_AC_CVS_CHANGES([
  SIM_AC_CVS_CHANGE([
    rm -rf conf-macros
    cvs co SoGuiExampleMacros
  ], [test -d cfg/m4], [test ! -d conf-macros])
])

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
  if $soguiconfig $alternate_option; then
    SIM_AC_CONFIGURATION_SETTING([Configuration Setting], ['$sim_ac_alternate_keyword'])
    GUI=`$soguiconfig $alternate_option --ac-subst GUI`
    Gui=`$soguiconfig $alternate_option --ac-subst Gui`
    gui=`$soguiconfig $alternate_option --ac-subst gui`
    WIDGET=`$soguiconfig $alternate_option --ac-subst WIDGET`
    EVENT=`$soguiconfig $alternate_option --ac-subst EVENT`
    COMPONENTHEADER=`$soguiconfig $alternate_option --ac-subst COMPONENTHEADER`
  elif $soguiconfig; then
    AC_MSG_WARN([configuration '$sim_ac_alternate_keyword' not found: fallback on default])
    SIM_AC_CONFIGURATION_SETTING([Configuration Setting], [default (fallback: $sim_ac_alternate_keyword not found)])
    GUI=`$soguiconfig $alternate_option --ac-subst GUI`
    Gui=`$soguiconfig $alternate_option --ac-subst Gui`
    gui=`$soguiconfig $alternate_option --ac-subst gui`
    WIDGET=`$soguiconfig $alternate_option --ac-subst WIDGET`
    EVENT=`$soguiconfig $alternate_option --ac-subst EVENT`
    COMPONENTHEADER=`$soguiconfig $alternate_option --ac-subst COMPONENTHEADER`
  else
    SIM_AC_ERROR([unable-to-run-soxx-config])
  fi

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
  [for SoIntersectionDetectionAction class],
  [#include <Inventor/collision/SoIntersectionDetectionAction.h>], [
   SoIntersectionDetectionAction ida;
   ida.setDraggersEnabled(FALSE);],
  [HAVE_SOINTERSECTIONDETECTIONACTION])

# **************************************************************************
# Remove redundant options from certain option lists, to clean up the
# compiler and linker invocations.

SIM_AC_UNIQIFY_LIST(CPPFLAGS, $CPPFLAGS)
SIM_AC_UNIQIFY_LIST(LDFLAGS, $LDFLAGS)
SIM_AC_UNIQIFY_LIST(LIBS, $LIBS)

# **************************************************************************
# All files configure must automatically generate.

AC_OUTPUT([
	Makefile
	components/Makefile
	coin-competitions/Makefile
	coin-competitions/SIM-20020503/Makefile
	coin-competitions/SIM-20020118/Makefile
	coin-competitions/SIM-20011116/Makefile
	coin-competitions/SIM-20011005/Makefile
	coin-competitions/SIM-20010914/Makefile
	coin-competitions/SIM-20010824/Makefile
	coin-competitions/SIM-20010803/Makefile
	eyecandy/Makefile
	actions/Makefile
	draggers/Makefile
	engines/Makefile
	manipulators/Makefile
	nodes/Makefile
	sensors/Makefile
	nodekits/Makefile
])

SIM_AC_CONFIGURATION_SUMMARY

echo ""
echo "Now run 'make' to build the examples."
echo ""
echo "(Note that they are not installed, so after building you should"
echo "execute them straight from this directory's subdirectories.)"
echo ""

# **************************************************************************
