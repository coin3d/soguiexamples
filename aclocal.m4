dnl aclocal.m4 generated automatically by aclocal 1.4-p4

dnl Copyright (C) 1994, 1995-8, 1999 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY, to the extent permitted by law; without
dnl even the implied warranty of MERCHANTABILITY or FITNESS FOR A
dnl PARTICULAR PURPOSE.

# **************************************************************************
# SIM_AC_CVS_CHANGES( SIM_AC_CVS_CHANGE-MACROS )
#
# This macro is just an envelope macro for SIM_AC_CVS_CHANGE invokations.
# It performs necessary initializations and finalizing.  All the
# SIM_AC_CVS_CHANGE invokations should be preformed inside the same
# SIM_AC_CVS_CHANGES macro.
#
# Authors:
#   Lars J. Aas <larsa@sim.no>
#

AC_DEFUN([SIM_AC_CVS_CHANGES], [
pushdef([sim_ac_cvs_changes], 1)
sim_ac_do_cvs_update=false
sim_ac_cvs_changed=false
sim_ac_cvs_problem=false
sim_ac_cvs_save_builddir=`pwd`
AC_ARG_ENABLE(
  [cvs-auto-update],
  AC_HELP_STRING([--enable-cvs-auto-update],
                 [auto-update CVS repository if possible]),
  [case "$enableval" in
  yes) sim_ac_do_cvs_update=true ;;
  no)  sim_ac_do_cvs_update=false ;;
  *)   AC_MSG_ERROR(["$enableval" given to --enable-cvs-update]) ;;
  esac])
if test -d $srcdir/CVS; then
  ifelse([$1], , :, [$1])
  if $sim_ac_cvs_problem; then
    cat <<"CVS_CHANGES_EOF"
To make the above listed procedure be executed automatically, run configure
again with "--enable-cvs-auto-update" added to the configure options.
CVS_CHANGES_EOF
  fi
fi
$sim_ac_cvs_problem && echo "" && echo "Aborting..." && exit 1
popdef([sim_ac_cvs_changes])
]) # SIM_AC_CVS_CHANGES

# **************************************************************************
# SIM_AC_CVS_CHANGE( UPDATE-PROCEDURE, UPDATE-TEST, UPDATE-TEST, ... )
#
# This macro is used to ensure that CVS source repository changes that need
# manual intervention on all the build systems are executed before the
# configure script is run.
#
# UPDATE-PROCEDURE is the procedure needed to update the source repository.
# UPDATE-TEST is a command that returns failure if the update procedure
# hasn't been executed, and success afterwards.  You can have as many test
# as you like.  All tests must pass for the macro to believe the source
# repository is up-to-date.
#
# All commands (the update procedure and the tests) are executed from the
# CVS repository root.
#
# SIM_AC_CVS_CHANGE must be invoked inside SIM_AC_CVS_CHANGES.
#
# Authors:
#   Lars J. Aas <larsa@sim.no>
#

AC_DEFUN([SIM_AC_CVS_CHANGE], [
ifdef([sim_ac_cvs_changes], ,
      [AC_MSG_ERROR([[SIM_AC_CVS_CHANGE invoked outside SIM_AC_CVS_CHANGES]])])
cd $srcdir;
m4_foreach([testcommand], [m4_shift($@)], [testcommand
if test $? -ne 0; then sim_ac_cvs_changed=true; fi
])
cd $sim_ac_cvs_save_builddir
if $sim_ac_cvs_changed; then
  if $sim_ac_do_cvs_update; then
    echo "Performing repository update:"
    cd $srcdir;
    ( set -x
$1 )
    sim_ac_cvs_unfixed=false
m4_foreach([testcommand], [m4_shift($@)],
[    testcommand
    if test $? -ne 0; then sim_ac_cvs_unfixed=true; fi
])
    cd $sim_ac_cvs_save_builddir
    if $sim_ac_cvs_unfixed; then
      cat <<"CVS_CHANGE_EOF"

The following update procedure does not seem to have produced the desired
effect:

$1

You should investigate what went wrong and alert the relevant software
developers about it.

Aborting...
CVS_CHANGE_EOF
      exit 1
    fi
  else
    $sim_ac_cvs_problem || {
    cat <<"CVS_CHANGE_EOF"

The configure script has detected source hierachy inconsistencies between
your source repository and the master source repository.  This needs to be
fixed before you can proceed.

The suggested update procedure is to execute the following set of commands
in the root source directory:
CVS_CHANGE_EOF
    }
    cat <<"CVS_CHANGE_EOF"
$1
CVS_CHANGE_EOF
    sim_ac_cvs_problem=true
  fi
fi
]) # SIM_AC_CVS_CHANGE

# EOF **********************************************************************

# **************************************************************************
# SIM_AC_SETUP_MSVC_IFELSE( IF-FOUND, IF-NOT-FOUND )
#
# This macro invokes IF-FOUND if the msvccc wrapper can be run, and
# IF-NOT-FOUND if not.
#
# Authors:
#   Morten Eriksen <mortene@coin3d.org>
#   Lars J. Aas <larsa@coin3d.org>

# **************************************************************************

AC_DEFUN([SIM_AC_SETUP_MSVC_IFELSE],
[# **************************************************************************
# If the Microsoft Visual C++ cl.exe compiler is available, set us up for
# compiling with it and to generate an MSWindows .dll file.

: ${BUILD_WITH_MSVC=false}
sim_ac_msvccc=`cd $srcdir; pwd`/cfg/m4/msvccc
if test -z "$CC" -a -z "$CXX" && $sim_ac_msvccc >/dev/null 2>&1; then
  m4_ifdef([$0_VISITED],
    [AC_FATAL([Macro $0 invoked multiple times])])
  m4_define([$0_VISITED], 1)
  CC=$sim_ac_msvccc
  CXX=$sim_ac_msvccc
  export CC CXX
  BUILD_WITH_MSVC=true
fi
AC_SUBST(BUILD_WITH_MSVC)
if $BUILD_WITH_MSVC; then
  :
  $1
else
  :
  $2
fi
]) # SIM_AC_SETUP_MSVC_IFELSE

# **************************************************************************

AC_DEFUN([SIM_AC_MSVC_SUPPORT],
[# **************************************************************************
# If the Microsoft Visual C++ cl.exe compiler is available, set us up for
# compiling with it and to generate an MSWindows .dll file.

: ${BUILD_WITH_MSVC=false}
sim_ac_msvccc=`cd $srcdir; pwd`/cfg/m4/msvccc
if test -z "$CC" -a -z "$CXX" && $sim_ac_msvccc >/dev/null 2>&1; then
  m4_ifdef([$0_VISITED],
    [AC_FATAL([Macro $0 invoked multiple times])])
  m4_define([$0_VISITED], 1)
  CC=$sim_ac_msvccc
  CXX=$sim_ac_msvccc
  export CC CXX
  BUILD_WITH_MSVC=true
fi
AC_SUBST(BUILD_WITH_MSVC)
]) # SIM_AC_MSVC_SUPPORT

# EOF **********************************************************************

# Do all the work for Automake.  This macro actually does too much --
# some checks are only needed if your package does certain things.
# But this isn't really a big deal.

# serial 1

dnl Usage:
dnl AM_INIT_AUTOMAKE(package,version, [no-define])

AC_DEFUN(AM_INIT_AUTOMAKE,
[AC_REQUIRE([AC_PROG_INSTALL])
PACKAGE=[$1]
AC_SUBST(PACKAGE)
VERSION=[$2]
AC_SUBST(VERSION)
dnl test to see if srcdir already configured
if test "`cd $srcdir && pwd`" != "`pwd`" && test -f $srcdir/config.status; then
  AC_MSG_ERROR([source directory already configured; run "make distclean" there first])
fi
ifelse([$3],,
AC_DEFINE_UNQUOTED(PACKAGE, "$PACKAGE", [Name of package])
AC_DEFINE_UNQUOTED(VERSION, "$VERSION", [Version number of package]))
AC_REQUIRE([AM_SANITY_CHECK])
AC_REQUIRE([AC_ARG_PROGRAM])
dnl FIXME This is truly gross.
missing_dir=`cd $ac_aux_dir && pwd`
AM_MISSING_PROG(ACLOCAL, aclocal, $missing_dir)
AM_MISSING_PROG(AUTOCONF, autoconf, $missing_dir)
AM_MISSING_PROG(AUTOMAKE, automake, $missing_dir)
AM_MISSING_PROG(AUTOHEADER, autoheader, $missing_dir)
AM_MISSING_PROG(MAKEINFO, makeinfo, $missing_dir)
AC_REQUIRE([AC_PROG_MAKE_SET])])

#
# Check to make sure that the build environment is sane.
#

AC_DEFUN(AM_SANITY_CHECK,
[AC_MSG_CHECKING([whether build environment is sane])
# Just in case
sleep 1
echo timestamp > conftestfile
# Do `set' in a subshell so we don't clobber the current shell's
# arguments.  Must try -L first in case configure is actually a
# symlink; some systems play weird games with the mod time of symlinks
# (eg FreeBSD returns the mod time of the symlink's containing
# directory).
if (
   set X `ls -Lt $srcdir/configure conftestfile 2> /dev/null`
   if test "[$]*" = "X"; then
      # -L didn't work.
      set X `ls -t $srcdir/configure conftestfile`
   fi
   if test "[$]*" != "X $srcdir/configure conftestfile" \
      && test "[$]*" != "X conftestfile $srcdir/configure"; then

      # If neither matched, then we have a broken ls.  This can happen
      # if, for instance, CONFIG_SHELL is bash and it inherits a
      # broken ls alias from the environment.  This has actually
      # happened.  Such a system could not be considered "sane".
      AC_MSG_ERROR([ls -t appears to fail.  Make sure there is not a broken
alias in your environment])
   fi

   test "[$]2" = conftestfile
   )
then
   # Ok.
   :
else
   AC_MSG_ERROR([newly created file is older than distributed files!
Check your system clock])
fi
rm -f conftest*
AC_MSG_RESULT(yes)])

dnl AM_MISSING_PROG(NAME, PROGRAM, DIRECTORY)
dnl The program must properly implement --version.
AC_DEFUN(AM_MISSING_PROG,
[AC_MSG_CHECKING(for working $2)
# Run test in a subshell; some versions of sh will print an error if
# an executable is not found, even if stderr is redirected.
# Redirect stdin to placate older versions of autoconf.  Sigh.
if ($2 --version) < /dev/null > /dev/null 2>&1; then
   $1=$2
   AC_MSG_RESULT(found)
else
   $1="$3/missing $2"
   AC_MSG_RESULT(missing)
fi
AC_SUBST($1)])

# Like AC_CONFIG_HEADER, but automatically create stamp file.

AC_DEFUN(AM_CONFIG_HEADER,
[AC_PREREQ([2.12])
AC_CONFIG_HEADER([$1])
dnl When config.status generates a header, we must update the stamp-h file.
dnl This file resides in the same directory as the config header
dnl that is generated.  We must strip everything past the first ":",
dnl and everything past the last "/".
AC_OUTPUT_COMMANDS(changequote(<<,>>)dnl
ifelse(patsubst(<<$1>>, <<[^ ]>>, <<>>), <<>>,
<<test -z "<<$>>CONFIG_HEADERS" || echo timestamp > patsubst(<<$1>>, <<^\([^:]*/\)?.*>>, <<\1>>)stamp-h<<>>dnl>>,
<<am_indx=1
for am_file in <<$1>>; do
  case " <<$>>CONFIG_HEADERS " in
  *" <<$>>am_file "*<<)>>
    echo timestamp > `echo <<$>>am_file | sed -e 's%:.*%%' -e 's%[^/]*$%%'`stamp-h$am_indx
    ;;
  esac
  am_indx=`expr "<<$>>am_indx" + 1`
done<<>>dnl>>)
changequote([,]))])

# Add --enable-maintainer-mode option to configure.
# From Jim Meyering

# serial 1

AC_DEFUN(AM_MAINTAINER_MODE,
[AC_MSG_CHECKING([whether to enable maintainer-specific portions of Makefiles])
  dnl maintainer-mode is disabled by default
  AC_ARG_ENABLE(maintainer-mode,
[  --enable-maintainer-mode enable make rules and dependencies not useful
                          (and sometimes confusing) to the casual installer],
      USE_MAINTAINER_MODE=$enableval,
      USE_MAINTAINER_MODE=no)
  AC_MSG_RESULT($USE_MAINTAINER_MODE)
  AM_CONDITIONAL(MAINTAINER_MODE, test $USE_MAINTAINER_MODE = yes)
  MAINT=$MAINTAINER_MODE_TRUE
  AC_SUBST(MAINT)dnl
]
)

# Define a conditional.

AC_DEFUN(AM_CONDITIONAL,
[AC_SUBST($1_TRUE)
AC_SUBST($1_FALSE)
if $2; then
  $1_TRUE=
  $1_FALSE='#'
else
  $1_TRUE='#'
  $1_FALSE=
fi])

# Usage:
#   SIM_AC_COMPILE_DEBUG([ACTION-IF-DEBUG[, ACTION-IF-NOT-DEBUG]])
#
# Description:
#   Let the user decide if compilation should be done in "debug mode".
#   If compilation is not done in debug mode, all assert()'s in the code
#   will be disabled.
#
#   Also sets enable_debug variable to either "yes" or "no", so the
#   configure.in writer can add package-specific actions. Default is "yes".
#   This was also extended to enable the developer to set up the two first
#   macro arguments following the well-known ACTION-IF / ACTION-IF-NOT
#   concept.
#
# Authors:
#   Morten Eriksen, <mortene@sim.no>
#   Lars J. Aas, <larsa@sim.no>
#

AC_DEFUN([SIM_AC_COMPILE_DEBUG], [
AC_ARG_ENABLE(
  [debug],
  AC_HELP_STRING([--enable-debug], [compile in debug mode [[default=yes]]]),
  [case "${enableval}" in
    yes) enable_debug=true ;;
    no)  enable_debug=false ;;
    true | false) enable_debug=${enableval} ;;
    *) AC_MSG_ERROR(bad value "${enableval}" for --enable-debug) ;;
  esac],
  [enable_debug=true])

if $enable_debug; then
  DSUFFIX=d
  ifelse([$1], , :, [$1])
else
  DSUFFIX=
  CPPFLAGS="$CPPFLAGS -DNDEBUG"
  ifelse([$2], , :, [$2])
fi
AC_SUBST(DSUFFIX)
])


# Usage:
#   SIM_AC_DEBUGSYMBOLS
#
# Description:
#   Let the user decide if debug symbol information should be compiled
#   in. The compiled libraries/executables will use a lot less space
#   if stripped for their symbol information.
# 
#   Note: this macro must be placed after either AC_PROG_CC or AC_PROG_CXX
#   in the configure.in script.
# 
# Author: Morten Eriksen, <mortene@sim.no>.
# 

AC_DEFUN([SIM_AC_DEBUGSYMBOLS], [
AC_ARG_ENABLE(
  [symbols],
  AC_HELP_STRING([--enable-symbols],
                 [include symbol debug information [[default=yes]]]),
  [case "${enableval}" in
    yes) enable_symbols=yes ;;
    no)  enable_symbols=no ;;
    *) AC_MSG_ERROR(bad value "${enableval}" for --enable-symbols) ;;
  esac],
  [enable_symbols=yes])

if test x"$enable_symbols" = x"no"; then
  CFLAGS="`echo $CFLAGS | sed 's/-g//'`"
  CPPFLAGS="`echo $CPPFLAGS | sed 's/-g//'`"
  CXXFLAGS="`echo $CXXFLAGS | sed 's/-g//'`"
fi
])

# Usage:
#   SIM_AC_RTTI_SUPPORT
#
# Description:
#   Let the user decide if RTTI should be compiled in. The compiled
#   libraries/executables will use a lot less space if they don't
#   contain RTTI.
# 
#   Note: this macro must be placed after AC_PROG_CXX in the
#   configure.in script.
# 
# Author: Morten Eriksen, <mortene@sim.no>.

AC_DEFUN([SIM_AC_RTTI_SUPPORT], [
AC_PREREQ([2.13])
AC_ARG_ENABLE(
  [rtti],
  AC_HELP_STRING([--enable-rtti], [(g++ only) compile with RTTI [[default=yes]]]),
  [case "${enableval}" in
    yes) enable_rtti=yes ;;
    no)  enable_rtti=no ;;
    *) AC_MSG_ERROR(bad value "${enableval}" for --enable-rtti) ;;
  esac],
  [enable_rtti=yes])

if test x"$enable_rtti" = x"no"; then
  if test x"$GXX" = x"yes"; then
    CXXFLAGS="$CXXFLAGS -fno-rtti"
  else
    AC_MSG_WARN([--enable-rtti only has effect when using GNU g++])
  fi
fi
])

# Usage:
#   SIM_CHECK_EXCEPTION_HANDLING
#
# Description:
#   Let the user decide if C++ exception handling should be compiled
#   in. The compiled libraries/executables will use a lot less space
#   if they have exception handling support.
#
#   Note: this macro must be placed after AC_PROG_CXX in the
#   configure.in script.
#
#   Author: Morten Eriksen, <mortene@sim.no>.
#
# TODO:
#   * [mortene:19991114] make this work with compilers other than gcc/g++
#

AC_DEFUN([SIM_EXCEPTION_HANDLING], [
AC_PREREQ([2.13])
AC_ARG_ENABLE(
  [exceptions],
  AC_HELP_STRING([--enable-exceptions],
                 [(g++ only) compile with exceptions [[default=no]]]),
  [case "${enableval}" in
    yes) enable_exceptions=yes ;;
    no)  enable_exceptions=no ;;
    *) AC_MSG_ERROR(bad value "${enableval}" for --enable-exceptions) ;;
  esac],
  [enable_exceptions=no])

if test x"$enable_exceptions" = x"no"; then
  if test "x$GXX" = "xyes"; then
    unset _exception_flag
    dnl This is for GCC >= 2.8
    SIM_AC_CXX_COMPILER_OPTION([-fno-exceptions], [_exception_flag=-fno-exceptions])
    if test x"${_exception_flag+set}" != x"set"; then
      dnl For GCC versions < 2.8
      SIM_AC_CXX_COMPILER_OPTION([-fno-handle-exceptions],
                                 [_exception_flag=-fno-handle-exceptions])
    fi
    if test x"${_exception_flag+set}" != x"set"; then
      AC_MSG_WARN([couldn't find a valid option for avoiding exception handling])
    else
      CXXFLAGS="$CXXFLAGS $_exception_flag"
    fi
  fi
else
  if test x"$GXX" != x"yes"; then
    AC_MSG_WARN([--enable-exceptions only has effect when using GNU g++])
  fi
fi
])


#   Use this file to store miscellaneous macros related to checking
#   compiler features.

# Usage:
#   SIM_AC_CC_COMPILER_OPTION(OPTION-TO-TEST, ACTION-IF-TRUE [, ACTION-IF-FALSE])
#   SIM_AC_CXX_COMPILER_OPTION(OPTION-TO-TEST, ACTION-IF-TRUE [, ACTION-IF-FALSE])
#
# Description:
#
#   Check whether the current C or C++ compiler can handle a
#   particular command-line option.
#
#
# Author: Morten Eriksen, <mortene@sim.no>.
#
#   * [mortene:19991218] improve macros by catching and analyzing
#     stderr (at least to see if there was any output there)?
#

AC_DEFUN([SIM_AC_COMPILER_OPTION], [
sim_ac_save_cppflags=$CPPFLAGS
CPPFLAGS="$CPPFLAGS $1"
AC_TRY_COMPILE([], [], [sim_ac_accept_result=yes], [sim_ac_accept_result=no])
AC_MSG_RESULT([$sim_ac_accept_result])
CPPFLAGS=$sim_ac_save_cppflags
# This need to go last, in case CPPFLAGS is modified in $2 or $3.
if test $sim_ac_accept_result = yes; then
  ifelse($2, , :, $2)
else
  ifelse($3, , :, $3)
fi
])

AC_DEFUN([SIM_AC_CC_COMPILER_OPTION], [
AC_LANG_SAVE
AC_LANG_C
AC_MSG_CHECKING([whether $CC accepts $1])
SIM_AC_COMPILER_OPTION($1, $2, $3)
AC_LANG_RESTORE
])

AC_DEFUN([SIM_AC_CXX_COMPILER_OPTION], [
AC_LANG_SAVE
AC_LANG_CPLUSPLUS
AC_MSG_CHECKING([whether $CXX accepts $1])
SIM_AC_COMPILER_OPTION($1, $2, $3)
AC_LANG_RESTORE
])

# Usage:
#   SIM_PROFILING_SUPPORT
#
# Description:
#   Let the user decide if profiling code should be compiled
#   in. The compiled libraries/executables will use a lot less space
#   if they don't contain profiling code information, and they will also
#   execute faster.
#
#   Note: this macro must be placed after either AC_PROG_CC or AC_PROG_CXX
#   in the configure.in script.
#
# Author: Morten Eriksen, <mortene@sim.no>.
#
# TODO:
#   * [mortene:19991114] make this work with compilers other than gcc/g++
#

AC_DEFUN([SIM_PROFILING_SUPPORT], [
AC_PREREQ([2.13])
AC_ARG_ENABLE(
  [profile],
  AC_HELP_STRING([--enable-profile],
                 [(GCC only) turn on inclusion of profiling code [[default=no]]]),
  [case "${enableval}" in
    yes) enable_profile=yes ;;
    no)  enable_profile=no ;;
    *) AC_MSG_ERROR(bad value "${enableval}" for --enable-profile) ;;
  esac],
  [enable_profile=no])

if test x"$enable_profile" = x"yes"; then
  if test x"$GXX" = x"yes" || test x"$GCC" = x"yes"; then
    CFLAGS="$CFLAGS -pg"
    CXXFLAGS="$CXXFLAGS -pg"
    LDFLAGS="$LDFLAGS -pg"
  else
    AC_MSG_WARN([--enable-profile only has effect when using GNU gcc or g++])
  fi
fi
])


# Usage:
#   SIM_COMPILER_WARNINGS
#
# Description:
#   Take care of making a sensible selection of warning messages
#   to turn on or off.
# 
#   Note: this macro must be placed after either AC_PROG_CC or AC_PROG_CXX
#   in the configure.in script.
# 
# Author: Morten Eriksen, <mortene@sim.no>.
# 
# TODO:
#   * [mortene:19991114] find out how to get GCC's
#     -Werror-implicit-function-declaration option to work as expected
#
#   * [mortene:20000606] there are a few assumptions here which doesn't
#     necessarily hold water: both the C and C++ compiler doesn't have
#     to be "compatible", i.e. the C compiler could be gcc, while the
#     C++ compiler could be a native compiler, for instance. So some
#     restructuring should be done.
# 
#   * [larsa:20000607] don't check all -woff options to SGI MIPSpro CC,
#     just put all of them on the same line, to check if the syntax is ok.
#   * [larsa:20010504] rename to SIM_AC_COMPILER_WARNINGS and clean up
#     the macro

AC_DEFUN([SIM_COMPILER_WARNINGS], [
AC_ARG_ENABLE(
  [warnings],
  AC_HELP_STRING([--enable-warnings],
                 [turn on warnings when compiling [[default=yes]]]),
  [case "${enableval}" in
    yes) enable_warnings=yes ;;
    no)  enable_warnings=no ;;
    *) AC_MSG_ERROR(bad value "${enableval}" for --enable-warnings) ;;
  esac],
  [enable_warnings=yes])

if test x"$enable_warnings" = x"yes"; then
  if test x"$GXX" = x"yes" || test x"$GCC" = x"yes"; then
    sim_ac_common_gcc_warnings="-W -Wall -Wno-unused"
    # -fno-multichar can be different for gcc and egcs c++, for instance,
    # so we need to do separate checks.
    if test x"$CC" = x"$CXX"; then
      CPPFLAGS="$CPPFLAGS $sim_ac_common_gcc_warnings"
      SIM_AC_CXX_COMPILER_OPTION([-Wno-multichar], [CPPFLAGS="$CPPFLAGS -Wno-multichar"])
    else
      CFLAGS="$CFLAGS $sim_ac_common_gcc_warnings"
      SIM_AC_CC_COMPILER_OPTION([-Wno-multichar], [CFLAGS="$CFLAGS -Wno-multichar"])
      CXXFLAGS="$CXXFLAGS $sim_ac_common_gcc_warnings"
      SIM_AC_CXX_COMPILER_OPTION([-Wno-multichar], [CXXFLAGS="$CXXFLAGS -Wno-multichar"])
    fi
  else
    case $host in
    *-*-irix*) 
      if test x"$CC" = xcc || test x"$CC" = xCC || test x"$CXX" = xCC; then
        _warn_flags=
        _woffs=""
        ### Turn on all warnings ######################################
        SIM_AC_CC_COMPILER_OPTION(-fullwarn, CPPFLAGS="$CPPFLAGS -fullwarn")

        ### Turn off specific (bogus) warnings ########################

        ### SGI MipsPro v?.?? (our compiler on IRIX 6.2) ##############
        ##
        ## 3115: ``type qualifiers are meaningless in this declaration''.
        ## 3262: unused variables.
        ##
        ### SGI MipsPro v7.30 #########################################
        ##
	## 1174: "The function was declared but never referenced."
        ## 1209: "The controlling expression is constant." (kill warning on
        ##       if (0), assert(FALSE), etc).
        ## 1355: Kill warnings on extra semicolons (which happens with some
        ##       of the Coin macros).
        ## 1375: Non-virtual destructors in base classes.
        ## 3201: Unused argument to a function.
        ## 1110: "Statement is not reachable" (the Lex/Flex generated code in
        ##       Coin/src/engines has lots of shitty code which needs this).
        ## 1506: Implicit conversion from "unsigned long" to "long".
        ##       SbTime.h in SGI/TGS Inventor does this, so we need to kill
        ##       this warning to avoid all the output clutter when compiling
        ##       the SoQt, SoGtk or SoXt libraries on IRIX with SGI MIPSPro CC.

        sim_ac_bogus_warnings="-woff 3115,3262,1174,1209,1355,1375,3201,1110,1506"
        SIM_AC_CC_COMPILER_OPTION($sim_ac_bogus_warnings,
                                  CPPFLAGS="$CPPFLAGS $sim_ac_bogus_warnings")
      fi
    ;;
    esac
  fi
else
  if test x"$GXX" != x"yes" && test x"$GCC" != x"yes"; then
    AC_MSG_WARN([--enable-warnings only has effect when using GNU gcc or g++])
  fi
fi
])


# Usage:
#   SIM_AC_CHECK_MATHLIB([ACTION-IF-OK[, ACTION-IF-NOT-OK]])
#
# Description:
#   Check if linker needs to explicitly link with the library with
#   math functions. Sets environment variable $sim_ac_libm to the
#   necessary linklibrary, plus includes this library in the LIBS
#   env variable.
#
# Notes:
#   There is a macro AC_CHECK_LIBM in the libtool distribution, but it
#   does at least not work with SGI MIPSpro CC v7.30.
#
# Authors:
#   Lars J�rgen Aas, <larsa@sim.no>
#   Morten Eriksen, <mortene@sim.no>
#   Rupert Kittinger, <kittinger@mechanik.tu-graz.ac.at>
#

AC_DEFUN([SIM_AC_CHECK_MATHLIB],
[sim_ac_libm=

AC_CACHE_CHECK(
  [for math functions library],
  [sim_cv_lib_math],
  [sim_cv_lib_math=UNDEFINED
  # BeOS and MSWin platforms has implicit math library linking,
  # and ncr-sysv4.3 might use -lmw (according to AC_CHECK_LIBM in
  # libtool.m4).
  for sim_ac_math_chk in "" -lm -lmw; do
    if test x"$sim_cv_lib_math" = xUNDEFINED; then
      sim_ac_store_libs=$LIBS
      LIBS="$sim_ac_store_libs $sim_ac_math_chk"
      AC_TRY_LINK([#include <math.h>
                  #include <stdlib.h>
                  #include <stdio.h>],
                  [char s[16];
                   /*
                      SGI IRIX MIPSpro compilers may "fold" math
                      functions with constant arguments already
                      at compile time.

                      It is also theoretically possible to do this
                      for atof(), so to be _absolutely_ sure the
                      math functions aren't replaced by constants at
                      compile time, we get the arguments from a guaranteed
                      non-constant source (stdin).
                   */
                  fmod(atof(fgets(s,15,stdin)), atof(fgets(s,15,stdin)));
                  pow(atof(fgets(s,15,stdin)), atof(fgets(s,15,stdin)));
                  exp(atof(fgets(s,15,stdin)));
                  sin(atof(fgets(s,15,stdin)))],
                  [sim_cv_lib_math=$sim_ac_math_chk])
      LIBS=$sim_ac_store_libs
    fi
  done
  ])

if test x"$sim_cv_lib_math" != xUNDEFINED; then
  sim_ac_libm=$sim_cv_lib_math
  LIBS="$sim_ac_libm $LIBS"
  $1
else
  ifelse([$2], , :, [$2])
fi
])# SIM_AC_CHECK_MATHLIB

# **************************************************************************
# SIM_AC_MATHLIB_READY_IFELSE( [ACTION-IF-TRUE], [ACTION-IF-FALSE] )

AC_DEFUN([SIM_AC_MATHLIB_READY_IFELSE],
[AC_CACHE_CHECK(
  [if mathlib linkage is ready],
  [sim_cv_mathlib_ready],
  [AC_TRY_LINK(
    [#include <math.h>
    #include <stdlib.h>
    #include <stdio.h>],
    [char s[16];
    /*
    SGI IRIX MIPSpro compilers may "fold" math
    functions with constant arguments already
    at compile time.

    It is also theoretically possible to do this
    for atof(), so to be _absolutely_ sure the
    math functions aren't replaced by constants at
    compile time, we get the arguments from a guaranteed
    non-constant source (stdin).
    */
    printf("> %g\n",fmod(atof(fgets(s,15,stdin)), atof(fgets(s,15,stdin))));
    printf("> %g\n",pow(atof(fgets(s,15,stdin)), atof(fgets(s,15,stdin))));
    printf("> %g\n",exp(atof(fgets(s,15,stdin))));
    printf("> %g\n",sin(atof(fgets(s,15,stdin))))],
    [sim_cv_mathlib_ready=true],
    [sim_cv_mathlib_ready=false])])
if ${sim_cv_mathlib_ready}; then
  ifelse([$1], , :, [$1])
else
  ifelse([$2], , :, [$2])
fi
]) # SIM_AC_MATHLIB_READY_IFELSE()



# serial 40 AC_PROG_LIBTOOL
AC_DEFUN(AC_PROG_LIBTOOL,
[AC_REQUIRE([AC_LIBTOOL_SETUP])dnl

# Save cache, so that ltconfig can load it
AC_CACHE_SAVE

# Actually configure libtool.  ac_aux_dir is where install-sh is found.
CC="$CC" CFLAGS="$CFLAGS" CPPFLAGS="$CPPFLAGS" \
LD="$LD" LDFLAGS="$LDFLAGS" LIBS="$LIBS" \
LN_S="$LN_S" NM="$NM" RANLIB="$RANLIB" \
DLLTOOL="$DLLTOOL" AS="$AS" OBJDUMP="$OBJDUMP" \
${CONFIG_SHELL-/bin/sh} $ac_aux_dir/ltconfig --no-reexec \
$libtool_flags --no-verify $ac_aux_dir/ltmain.sh $lt_target \
|| AC_MSG_ERROR([libtool configure failed])

# Reload cache, that may have been modified by ltconfig
AC_CACHE_LOAD

# This can be used to rebuild libtool when needed
LIBTOOL_DEPS="$ac_aux_dir/ltconfig $ac_aux_dir/ltmain.sh"

# Always use our own libtool.
LIBTOOL='$(SHELL) $(top_builddir)/libtool'
AC_SUBST(LIBTOOL)dnl

# Redirect the config.log output again, so that the ltconfig log is not
# clobbered by the next message.
exec 5>>./config.log
])

AC_DEFUN(AC_LIBTOOL_SETUP,
[AC_PREREQ(2.13)dnl
AC_REQUIRE([AC_ENABLE_SHARED])dnl
AC_REQUIRE([AC_ENABLE_STATIC])dnl
AC_REQUIRE([AC_ENABLE_FAST_INSTALL])dnl
AC_REQUIRE([AC_CANONICAL_HOST])dnl
AC_REQUIRE([AC_CANONICAL_BUILD])dnl
AC_REQUIRE([AC_PROG_RANLIB])dnl
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_PROG_LD])dnl
AC_REQUIRE([AC_PROG_NM])dnl
AC_REQUIRE([AC_PROG_LN_S])dnl
dnl

case "$target" in
NONE) lt_target="$host" ;;
*) lt_target="$target" ;;
esac

# Check for any special flags to pass to ltconfig.
libtool_flags="--cache-file=$cache_file"
test "$enable_shared" = no && libtool_flags="$libtool_flags --disable-shared"
test "$enable_static" = no && libtool_flags="$libtool_flags --disable-static"
test "$enable_fast_install" = no && libtool_flags="$libtool_flags --disable-fast-install"
test "$ac_cv_prog_gcc" = yes && libtool_flags="$libtool_flags --with-gcc"
test "$ac_cv_prog_gnu_ld" = yes && libtool_flags="$libtool_flags --with-gnu-ld"
ifdef([AC_PROVIDE_AC_LIBTOOL_DLOPEN],
[libtool_flags="$libtool_flags --enable-dlopen"])
ifdef([AC_PROVIDE_AC_LIBTOOL_WIN32_DLL],
[libtool_flags="$libtool_flags --enable-win32-dll"])
AC_ARG_ENABLE(libtool-lock,
  [  --disable-libtool-lock  avoid locking (might break parallel builds)])
test "x$enable_libtool_lock" = xno && libtool_flags="$libtool_flags --disable-lock"
test x"$silent" = xyes && libtool_flags="$libtool_flags --silent"

# Some flags need to be propagated to the compiler or linker for good
# libtool support.
case "$lt_target" in
*-*-irix6*)
  # Find out which ABI we are using.
  echo '[#]line __oline__ "configure"' > conftest.$ac_ext
  if AC_TRY_EVAL(ac_compile); then
    case "`/usr/bin/file conftest.o`" in
    *32-bit*)
      LD="${LD-ld} -32"
      ;;
    *N32*)
      LD="${LD-ld} -n32"
      ;;
    *64-bit*)
      LD="${LD-ld} -64"
      ;;
    esac
  fi
  rm -rf conftest*
  ;;

*-*-sco3.2v5*)
  # On SCO OpenServer 5, we need -belf to get full-featured binaries.
  SAVE_CFLAGS="$CFLAGS"
  CFLAGS="$CFLAGS -belf"
  AC_CACHE_CHECK([whether the C compiler needs -belf], lt_cv_cc_needs_belf,
    [AC_TRY_LINK([],[],[lt_cv_cc_needs_belf=yes],[lt_cv_cc_needs_belf=no])])
  if test x"$lt_cv_cc_needs_belf" != x"yes"; then
    # this is probably gcc 2.8.0, egcs 1.0 or newer; no need for -belf
    CFLAGS="$SAVE_CFLAGS"
  fi
  ;;

ifdef([AC_PROVIDE_AC_LIBTOOL_WIN32_DLL],
[*-*-cygwin* | *-*-mingw*)
  AC_CHECK_TOOL(DLLTOOL, dlltool, false)
  AC_CHECK_TOOL(AS, as, false)
  AC_CHECK_TOOL(OBJDUMP, objdump, false)
  ;;
])
esac
])

# AC_LIBTOOL_DLOPEN - enable checks for dlopen support
AC_DEFUN(AC_LIBTOOL_DLOPEN, [AC_BEFORE([$0],[AC_LIBTOOL_SETUP])])

# AC_LIBTOOL_WIN32_DLL - declare package support for building win32 dll's
AC_DEFUN(AC_LIBTOOL_WIN32_DLL, [AC_BEFORE([$0], [AC_LIBTOOL_SETUP])])

# AC_ENABLE_SHARED - implement the --enable-shared flag
# Usage: AC_ENABLE_SHARED[(DEFAULT)]
#   Where DEFAULT is either `yes' or `no'.  If omitted, it defaults to
#   `yes'.
AC_DEFUN(AC_ENABLE_SHARED, [dnl
define([AC_ENABLE_SHARED_DEFAULT], ifelse($1, no, no, yes))dnl
AC_ARG_ENABLE(shared,
changequote(<<, >>)dnl
<<  --enable-shared[=PKGS]  build shared libraries [default=>>AC_ENABLE_SHARED_DEFAULT],
changequote([, ])dnl
[p=${PACKAGE-default}
case "$enableval" in
yes) enable_shared=yes ;;
no) enable_shared=no ;;
*)
  enable_shared=no
  # Look at the argument we got.  We use all the common list separators.
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:,"
  for pkg in $enableval; do
    if test "X$pkg" = "X$p"; then
      enable_shared=yes
    fi
  done
  IFS="$ac_save_ifs"
  ;;
esac],
enable_shared=AC_ENABLE_SHARED_DEFAULT)dnl
])

# AC_DISABLE_SHARED - set the default shared flag to --disable-shared
AC_DEFUN(AC_DISABLE_SHARED, [AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
AC_ENABLE_SHARED(no)])

# AC_ENABLE_STATIC - implement the --enable-static flag
# Usage: AC_ENABLE_STATIC[(DEFAULT)]
#   Where DEFAULT is either `yes' or `no'.  If omitted, it defaults to
#   `yes'.
AC_DEFUN(AC_ENABLE_STATIC, [dnl
define([AC_ENABLE_STATIC_DEFAULT], ifelse($1, no, no, yes))dnl
AC_ARG_ENABLE(static,
changequote(<<, >>)dnl
<<  --enable-static[=PKGS]  build static libraries [default=>>AC_ENABLE_STATIC_DEFAULT],
changequote([, ])dnl
[p=${PACKAGE-default}
case "$enableval" in
yes) enable_static=yes ;;
no) enable_static=no ;;
*)
  enable_static=no
  # Look at the argument we got.  We use all the common list separators.
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:,"
  for pkg in $enableval; do
    if test "X$pkg" = "X$p"; then
      enable_static=yes
    fi
  done
  IFS="$ac_save_ifs"
  ;;
esac],
enable_static=AC_ENABLE_STATIC_DEFAULT)dnl
])

# AC_DISABLE_STATIC - set the default static flag to --disable-static
AC_DEFUN(AC_DISABLE_STATIC, [AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
AC_ENABLE_STATIC(no)])


# AC_ENABLE_FAST_INSTALL - implement the --enable-fast-install flag
# Usage: AC_ENABLE_FAST_INSTALL[(DEFAULT)]
#   Where DEFAULT is either `yes' or `no'.  If omitted, it defaults to
#   `yes'.
AC_DEFUN(AC_ENABLE_FAST_INSTALL, [dnl
define([AC_ENABLE_FAST_INSTALL_DEFAULT], ifelse($1, no, no, yes))dnl
AC_ARG_ENABLE(fast-install,
changequote(<<, >>)dnl
<<  --enable-fast-install[=PKGS]  optimize for fast installation [default=>>AC_ENABLE_FAST_INSTALL_DEFAULT],
changequote([, ])dnl
[p=${PACKAGE-default}
case "$enableval" in
yes) enable_fast_install=yes ;;
no) enable_fast_install=no ;;
*)
  enable_fast_install=no
  # Look at the argument we got.  We use all the common list separators.
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}:,"
  for pkg in $enableval; do
    if test "X$pkg" = "X$p"; then
      enable_fast_install=yes
    fi
  done
  IFS="$ac_save_ifs"
  ;;
esac],
enable_fast_install=AC_ENABLE_FAST_INSTALL_DEFAULT)dnl
])

# AC_ENABLE_FAST_INSTALL - set the default to --disable-fast-install
AC_DEFUN(AC_DISABLE_FAST_INSTALL, [AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
AC_ENABLE_FAST_INSTALL(no)])

# AC_PROG_LD - find the path to the GNU or non-GNU linker
AC_DEFUN(AC_PROG_LD,
[AC_ARG_WITH(gnu-ld,
[  --with-gnu-ld           assume the C compiler uses GNU ld [default=no]],
test "$withval" = no || with_gnu_ld=yes, with_gnu_ld=no)
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_CANONICAL_HOST])dnl
AC_REQUIRE([AC_CANONICAL_BUILD])dnl
ac_prog=ld
if test "$ac_cv_prog_gcc" = yes; then
  # Check if gcc -print-prog-name=ld gives a path.
  AC_MSG_CHECKING([for ld used by GCC])
  ac_prog=`($CC -print-prog-name=ld) 2>&5`
  case "$ac_prog" in
    # Accept absolute paths.
changequote(,)dnl
    [\\/]* | [A-Za-z]:[\\/]*)
      re_direlt='/[^/][^/]*/\.\./'
changequote([,])dnl
      # Canonicalize the path of ld
      ac_prog=`echo $ac_prog| sed 's%\\\\%/%g'`
      while echo $ac_prog | grep "$re_direlt" > /dev/null 2>&1; do
	ac_prog=`echo $ac_prog| sed "s%$re_direlt%/%"`
      done
      test -z "$LD" && LD="$ac_prog"
      ;;
  "")
    # If it fails, then pretend we aren't using GCC.
    ac_prog=ld
    ;;
  *)
    # If it is relative, then search for the first ld in PATH.
    with_gnu_ld=unknown
    ;;
  esac
elif test "$with_gnu_ld" = yes; then
  AC_MSG_CHECKING([for GNU ld])
else
  AC_MSG_CHECKING([for non-GNU ld])
fi
AC_CACHE_VAL(ac_cv_path_LD,
[if test -z "$LD"; then
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}${PATH_SEPARATOR-:}"
  for ac_dir in $PATH; do
    test -z "$ac_dir" && ac_dir=.
    if test -f "$ac_dir/$ac_prog" || test -f "$ac_dir/$ac_prog$ac_exeext"; then
      ac_cv_path_LD="$ac_dir/$ac_prog"
      # Check to see if the program is GNU ld.  I'd rather use --version,
      # but apparently some GNU ld's only accept -v.
      # Break only if it was the GNU/non-GNU ld that we prefer.
      if "$ac_cv_path_LD" -v 2>&1 < /dev/null | egrep '(GNU|with BFD)' > /dev/null; then
	test "$with_gnu_ld" != no && break
      else
	test "$with_gnu_ld" != yes && break
      fi
    fi
  done
  IFS="$ac_save_ifs"
else
  ac_cv_path_LD="$LD" # Let the user override the test with a path.
fi])
LD="$ac_cv_path_LD"
if test -n "$LD"; then
  AC_MSG_RESULT($LD)
else
  AC_MSG_RESULT(no)
fi
test -z "$LD" && AC_MSG_ERROR([no acceptable ld found in \$PATH])
AC_PROG_LD_GNU
])

AC_DEFUN(AC_PROG_LD_GNU,
[AC_CACHE_CHECK([if the linker ($LD) is GNU ld], ac_cv_prog_gnu_ld,
[# I'd rather use --version here, but apparently some GNU ld's only accept -v.
if $LD -v 2>&1 </dev/null | egrep '(GNU|with BFD)' 1>&5; then
  ac_cv_prog_gnu_ld=yes
else
  ac_cv_prog_gnu_ld=no
fi])
])

# AC_PROG_NM - find the path to a BSD-compatible name lister
AC_DEFUN(AC_PROG_NM,
[AC_MSG_CHECKING([for BSD-compatible nm])
AC_CACHE_VAL(ac_cv_path_NM,
[if test -n "$NM"; then
  # Let the user override the test.
  ac_cv_path_NM="$NM"
else
  IFS="${IFS= 	}"; ac_save_ifs="$IFS"; IFS="${IFS}${PATH_SEPARATOR-:}"
  for ac_dir in $PATH /usr/ccs/bin /usr/ucb /bin; do
    test -z "$ac_dir" && ac_dir=.
    if test -f $ac_dir/nm || test -f $ac_dir/nm$ac_exeext ; then
      # Check to see if the nm accepts a BSD-compat flag.
      # Adding the `sed 1q' prevents false positives on HP-UX, which says:
      #   nm: unknown option "B" ignored
      if ($ac_dir/nm -B /dev/null 2>&1 | sed '1q'; exit 0) | egrep /dev/null >/dev/null; then
	ac_cv_path_NM="$ac_dir/nm -B"
	break
      elif ($ac_dir/nm -p /dev/null 2>&1 | sed '1q'; exit 0) | egrep /dev/null >/dev/null; then
	ac_cv_path_NM="$ac_dir/nm -p"
	break
      else
	ac_cv_path_NM=${ac_cv_path_NM="$ac_dir/nm"} # keep the first match, but
	continue # so that we can try to find one that supports BSD flags
      fi
    fi
  done
  IFS="$ac_save_ifs"
  test -z "$ac_cv_path_NM" && ac_cv_path_NM=nm
fi])
NM="$ac_cv_path_NM"
AC_MSG_RESULT([$NM])
])

# AC_CHECK_LIBM - check for math library
AC_DEFUN(AC_CHECK_LIBM,
[AC_REQUIRE([AC_CANONICAL_HOST])dnl
LIBM=
case "$lt_target" in
*-*-beos* | *-*-cygwin*)
  # These system don't have libm
  ;;
*-ncr-sysv4.3*)
  AC_CHECK_LIB(mw, _mwvalidcheckl, LIBM="-lmw")
  AC_CHECK_LIB(m, main, LIBM="$LIBM -lm")
  ;;
*)
  AC_CHECK_LIB(m, main, LIBM="-lm")
  ;;
esac
])

# AC_LIBLTDL_CONVENIENCE[(dir)] - sets LIBLTDL to the link flags for
# the libltdl convenience library and INCLTDL to the include flags for
# the libltdl header and adds --enable-ltdl-convenience to the
# configure arguments.  Note that LIBLTDL and INCLTDL are not
# AC_SUBSTed, nor is AC_CONFIG_SUBDIRS called.  If DIR is not
# provided, it is assumed to be `libltdl'.  LIBLTDL will be prefixed
# with '${top_builddir}/' and INCLTDL will be prefixed with
# '${top_srcdir}/' (note the single quotes!).  If your package is not
# flat and you're not using automake, define top_builddir and
# top_srcdir appropriately in the Makefiles.
AC_DEFUN(AC_LIBLTDL_CONVENIENCE, [AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
  case "$enable_ltdl_convenience" in
  no) AC_MSG_ERROR([this package needs a convenience libltdl]) ;;
  "") enable_ltdl_convenience=yes
      ac_configure_args="$ac_configure_args --enable-ltdl-convenience" ;;
  esac
  LIBLTDL='${top_builddir}/'ifelse($#,1,[$1],['libltdl'])/libltdlc.la
  INCLTDL='-I${top_srcdir}/'ifelse($#,1,[$1],['libltdl'])
])

# AC_LIBLTDL_INSTALLABLE[(dir)] - sets LIBLTDL to the link flags for
# the libltdl installable library and INCLTDL to the include flags for
# the libltdl header and adds --enable-ltdl-install to the configure
# arguments.  Note that LIBLTDL and INCLTDL are not AC_SUBSTed, nor is
# AC_CONFIG_SUBDIRS called.  If DIR is not provided and an installed
# libltdl is not found, it is assumed to be `libltdl'.  LIBLTDL will
# be prefixed with '${top_builddir}/' and INCLTDL will be prefixed
# with '${top_srcdir}/' (note the single quotes!).  If your package is
# not flat and you're not using automake, define top_builddir and
# top_srcdir appropriately in the Makefiles.
# In the future, this macro may have to be called after AC_PROG_LIBTOOL.
AC_DEFUN(AC_LIBLTDL_INSTALLABLE, [AC_BEFORE([$0],[AC_LIBTOOL_SETUP])dnl
  AC_CHECK_LIB(ltdl, main,
  [test x"$enable_ltdl_install" != xyes && enable_ltdl_install=no],
  [if test x"$enable_ltdl_install" = xno; then
     AC_MSG_WARN([libltdl not installed, but installation disabled])
   else
     enable_ltdl_install=yes
   fi
  ])
  if test x"$enable_ltdl_install" = x"yes"; then
    ac_configure_args="$ac_configure_args --enable-ltdl-install"
    LIBLTDL='${top_builddir}/'ifelse($#,1,[$1],['libltdl'])/libltdl.la
    INCLTDL='-I${top_srcdir}/'ifelse($#,1,[$1],['libltdl'])
  else
    ac_configure_args="$ac_configure_args --enable-ltdl-install=no"
    LIBLTDL="-lltdl"
    INCLTDL=
  fi
])

dnl old names
AC_DEFUN(AM_PROG_LIBTOOL, [indir([AC_PROG_LIBTOOL])])dnl
AC_DEFUN(AM_ENABLE_SHARED, [indir([AC_ENABLE_SHARED], $@)])dnl
AC_DEFUN(AM_ENABLE_STATIC, [indir([AC_ENABLE_STATIC], $@)])dnl
AC_DEFUN(AM_DISABLE_SHARED, [indir([AC_DISABLE_SHARED], $@)])dnl
AC_DEFUN(AM_DISABLE_STATIC, [indir([AC_DISABLE_STATIC], $@)])dnl
AC_DEFUN(AM_PROG_LD, [indir([AC_PROG_LD])])dnl
AC_DEFUN(AM_PROG_NM, [indir([AC_PROG_NM])])dnl

dnl This is just to silence aclocal about the macro not being used
ifelse([AC_DISABLE_FAST_INSTALL])dnl

# Usage:
#  SIM_AC_CHECK_DL([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
#
#  Try to find the dynamic link loader library. If it is found, these
#  shell variables are set:
#
#    $sim_ac_dl_cppflags (extra flags the compiler needs for dl lib)
#    $sim_ac_dl_ldflags  (extra flags the linker needs for dl lib)
#    $sim_ac_dl_libs     (link libraries the linker needs for dl lib)
#
#  The CPPFLAGS, LDFLAGS and LIBS flags will also be modified accordingly.
#  In addition, the variable $sim_ac_dl_avail is set to "yes" if
#  the dynamic link loader library is found.
#
#
# Author: Morten Eriksen, <mortene@sim.no>.

AC_DEFUN([SIM_AC_CHECK_DL], [
AC_ARG_WITH(
  [dl],
  [AC_HELP_STRING(
    [--with-dl=DIR],
    [include support for the dynamic link loader library [default=yes]])],
  [],
  [with_dl=yes])

sim_ac_dl_avail=no

if test x"$with_dl" != xno; then
  if test x"$with_dl" != xyes; then
    sim_ac_dl_cppflags="-I${with_dl}/include"
    sim_ac_dl_ldflags="-L${with_dl}/lib"
  fi
  sim_ac_dl_libs="-ldl"

  sim_ac_save_cppflags=$CPPFLAGS
  sim_ac_save_ldflags=$LDFLAGS
  sim_ac_save_libs=$LIBS

  CPPFLAGS="$CPPFLAGS $sim_ac_dl_cppflags"
  LDFLAGS="$LDFLAGS $sim_ac_dl_ldflags"
  LIBS="$sim_ac_dl_libs $LIBS"

  # Use SIM_AC_CHECK_HEADERS instead of .._HEADER to get the
  # HAVE_DLFCN_H symbol set up in config.h automatically.
  AC_CHECK_HEADERS([dlfcn.h])

  AC_CACHE_CHECK([whether the dynamic link loader library is available],
    sim_cv_lib_dl_avail,
    [AC_TRY_LINK([
#if HAVE_DLFCN_H
#include <dlfcn.h>
#endif /* HAVE_DLFCN_H */
],
                 [(void)dlopen(0L, 0);],
                 [sim_cv_lib_dl_avail=yes],
                 [sim_cv_lib_dl_avail=no])])

  if test x"$sim_cv_lib_dl_avail" = xyes; then
    sim_ac_dl_avail=yes
    ifelse([$1], , :, [$1])
  else
    CPPFLAGS=$sim_ac_save_cppflags
    LDFLAGS=$sim_ac_save_ldflags
    LIBS=$sim_ac_save_libs
    ifelse([$2], , :, [$2])
  fi
fi
])


# SIM_AC_CHECK_HEADER(HEADER-FILE, [ACTION-IF-FOUND], [ACTION-IF-NOT-FOUND])
# --------------------------------------------------------------------------
# Modified AC_CHECK_HEADER to use AC_TRY_COMPILE instead of AC_TRY_CPP,
# as we can get false positives and/or false negatives when running under
# Cygwin, using the Microsoft Visual C++ compiler (the configure script will
# pick the GCC preprocessor).

AC_DEFUN([SIM_AC_CHECK_HEADER], [
AC_VAR_PUSHDEF([ac_Header], [ac_cv_header_$1])
AC_ARG_VAR([CPPFLAGS], [C/C++ preprocessor flags, e.g. -I<include dir> if you have headers in a nonstandard directory <include dir>])
AC_CACHE_CHECK(
  [for $1],
  ac_Header,
  [AC_TRY_COMPILE([#include <$1>],
    [],
    [AC_VAR_SET([ac_Header], yes)],
    [AC_VAR_SET([ac_Header], no)])])
if test AC_VAR_GET(ac_Header) = yes; then
  ifelse([$2], , :, [$2])
else
  ifelse([$3], , :, [$3])
fi
AC_VAR_POPDEF([ac_Header])
])# SIM_AC_CHECK_HEADER


# SIM_AC_CHECK_HEADERS(HEADER-FILE...
#                  [ACTION-IF-FOUND], [ACTION-IF-NOT-FOUND])
# ----------------------------------------------------------
AC_DEFUN([SIM_AC_CHECK_HEADERS],
[for ac_header in $1
do
SIM_AC_CHECK_HEADER(
  [$ac_header],
  [AC_DEFINE_UNQUOTED(AC_TR_CPP(HAVE_$ac_header)) $2],
  [$3])
done
])# SIM_AC_CHECK_HEADERS


# SIM_AC_CHECK_SIZEOF(TYPE, [INCLUDES])
# --------------------------------------------
AC_DEFUN([SIM_AC_CHECK_SIZEOF],
[
AC_CHECK_TYPE([$1], [
  _AC_COMPUTE_INT([sizeof ($1)],
                  [sim_ac_bytesize],
                  [AC_INCLUDES_DEFAULT([$2])])
], [sim_ac_bytesize=0], [$2])
])# SIM_AC_CHECK_SIZEOF


# SIM_AC_BYTESIZE_TYPE(TYPEDEFTYPE, BYTESIZE, ALTERNATE_TYPELIST,
#                     [ACTION-IF-FOUND], [ACTION-IF-NOT-FOUND])
# ----------------------------------------------------------
# 
# FIXME: pretty ugly code with several quick hacks. 20010324 mortene.
AC_DEFUN([SIM_AC_BYTESIZE_TYPE],
[
sim_ac_searching=true
for sim_ac_type in $1 $3
do
  if $sim_ac_searching; then
    SIM_AC_CHECK_SIZEOF($sim_ac_type, [
#include <stdio.h>
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif /* HAVE_SYS_TYPES_H */
])
    if test "$sim_ac_bytesize" = "$2"; then
      sim_ac_searching=false
      if test "$sim_ac_type" = "$1"; then
        AC_DEFINE_UNQUOTED(AC_TR_CPP(have_$1), 1, [define this if the type is available on the system])
      fi
      AC_DEFINE_UNQUOTED(AC_TR_CPP(coin_$1), $sim_ac_type, [define this to a type of the indicated bitwidth])
    fi
  fi
done

if $sim_ac_searching; then
  ifelse([$5], , :, [$5])
else
  ifelse([$4], , :, [$4])
fi
])# SIM_AC_BYTESIZE_TYPE

# SIM_AC_DEFINE_BYTESIZE_TYPES
# ----------------------------------------------------------
# 
AC_DEFUN([SIM_AC_DEFINE_BYTESIZE_TYPES],
[
SIM_AC_BYTESIZE_TYPE(int8_t, 1, [char], [], AC_MSG_ERROR([could not find 8-bit type]))
SIM_AC_BYTESIZE_TYPE(uint8_t, 1, [u_int8_t "unsigned char"], [], AC_MSG_ERROR([could not find unsigned 8-bit type]))

SIM_AC_BYTESIZE_TYPE(int16_t, 2, [short int], [], AC_MSG_ERROR([could not find 16-bit type]))
SIM_AC_BYTESIZE_TYPE(uint16_t, 2, [u_int16_t "unsigned short" "unsigned int"], [], AC_MSG_ERROR([could not find unsigned 16-bit type]))

SIM_AC_BYTESIZE_TYPE(int32_t, 4, [int long], [], AC_MSG_ERROR([could not find 32-bit type]))
SIM_AC_BYTESIZE_TYPE(uint32_t, 4, [u_int32_t "unsigned int" "unsigned long"], [], AC_MSG_ERROR([could not find unsigned 32-bit type]))

SIM_AC_BYTESIZE_TYPE(int64_t, 8, [long int "long long" __int64], [], AC_MSG_WARN([could not find 64-bit type]))
SIM_AC_BYTESIZE_TYPE(uint64_t, 8, [u_int64_t "unsigned long" "unsigned int" "unsigned long long" "unsigned __int64"], [], AC_MSG_WARN([could not find unsigned 64-bit type]))
])# SIM_AC_DEFINE_BYTESIZE_TYPES

# Usage:
#  SIM_AC_CHECK_X11([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
#
#  Try to find the X11 development system. If it is found, these
#  shell variables are set:
#
#    $sim_ac_x11_cppflags (extra flags the compiler needs for X11)
#    $sim_ac_x11_ldflags  (extra flags the linker needs for X11)
#    $sim_ac_x11_libs     (link libraries the linker needs for X11)
#
#  The CPPFLAGS, LDFLAGS and LIBS flags will also be modified accordingly.
#  In addition, the variable $sim_ac_x11_avail is set to "yes" if
#  the X11 development system is found.
#
#
# Author: Morten Eriksen, <mortene@sim.no>.

AC_DEFUN([SIM_AC_CHECK_X11], [
AC_REQUIRE([AC_PATH_XTRA])

sim_ac_x11_avail=no

if test x"$no_x" != xyes; then
  #  *** DEBUG ***
  #  Keep this around, as it can be handy when testing on new systems.
  # echo "X_CFLAGS: $X_CFLAGS"
  # echo "X_PRE_LIBS: $X_PRE_LIBS"
  # echo "X_LIBS: $X_LIBS"
  # echo "X_EXTRA_LIBS: $X_EXTRA_LIBS"
  # echo
  # echo "CFLAGS: $CFLAGS"
  # echo "CPPFLAGS: $CPPFLAGS"
  # echo "CXXFLAGS: $CXXFLAGS"
  # echo "LDFLAGS: $LDFLAGS"
  # echo "LIBS: $LIBS"
  # exit 0

  sim_ac_x11_cppflags="$X_CFLAGS"
  sim_ac_x11_ldflags="$X_LIBS"
  sim_ac_x11_libs="$X_PRE_LIBS -lX11 $X_EXTRA_LIBS"

  sim_ac_save_cppflags=$CPPFLAGS
  sim_ac_save_ldflags=$LDFLAGS
  sim_ac_save_libs=$LIBS

  CPPFLAGS="$CPPFLAGS $sim_ac_x11_cppflags"
  LDFLAGS="$LDFLAGS $sim_ac_x11_ldflags"
  LIBS="$sim_ac_x11_libs $LIBS"

  AC_CACHE_CHECK(
    [whether we can link against X11],
    sim_cv_lib_x11_avail,
    [AC_TRY_LINK([#include <X11/Xlib.h>],
                 [(void)XOpenDisplay(0L);],
                 [sim_cv_lib_x11_avail=yes],
                 [sim_cv_lib_x11_avail=no])])

  if test x"$sim_cv_lib_x11_avail" = x"yes"; then
    sim_ac_x11_avail=yes
    $1
  else
    CPPFLAGS=$sim_ac_save_cppflags
    LDFLAGS=$sim_ac_save_ldflags
    LIBS=$sim_ac_save_libs
    $2
  fi
fi
])

# Usage:
#  SIM_AC_CHECK_X11SHMEM([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
#
#  Try to find the X11 shared memory extension. If it is found, this
#  shell variable is set:
#
#    $sim_ac_x11shmem_libs   (link libraries the linker needs for X11 Shm)
#
#  The LIBS flag will also be modified accordingly. In addition, the
#  variable $sim_ac_x11shmem_avail is set to "yes" if the X11 shared
#  memory extension is found.
#
#
# Author: Morten Eriksen, <mortene@sim.no>.
#
# TODO:
#    * [mortene:20000122] make sure this work on MSWin (with
#      Cygwin installation)
#

AC_DEFUN([SIM_AC_CHECK_X11SHMEM], [

sim_ac_x11shmem_avail=no
sim_ac_x11shmem_libs="-lXext"
sim_ac_save_libs=$LIBS
LIBS="$sim_ac_x11shmem_libs $LIBS"

AC_CACHE_CHECK(
  [whether the X11 shared memory extension is available],
  sim_cv_lib_x11shmem_avail,
  [AC_TRY_LINK([#include <X11/Xlib.h>
               #include <X11/extensions/XShm.h>],
               [(void)XShmQueryVersion(0L, 0L, 0L, 0L);],
               [sim_cv_lib_x11shmem_avail=yes],
               [sim_cv_lib_x11shmem_avail=no])])

if test x"$sim_cv_lib_x11shmem_avail" = xyes; then
  sim_ac_x11shmem_avail=yes
  $1
else
  LIBS=$sim_ac_save_libs
  $2
fi
])

# Usage:
#  SIM_AC_CHECK_X11MU([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
#
#  Try to find the X11 miscellaneous utilities extension. If it is
#  found, this shell variable is set:
#
#    $sim_ac_x11mu_libs   (link libraries the linker needs for X11 MU)
#
#  The LIBS flag will also be modified accordingly. In addition, the
#  variable $sim_ac_x11mu_avail is set to "yes" if the X11 miscellaneous
#  utilities extension is found.
#
# Author: Morten Eriksen, <mortene@sim.no>.
#
# TODO:
#    * [mortene:20000122] make sure this work on MSWin (with
#      Cygwin installation)
#

AC_DEFUN([SIM_AC_CHECK_X11MU], [

sim_ac_x11mu_avail=no
sim_ac_x11mu_libs="-lXmu"
sim_ac_save_libs=$LIBS
LIBS="$sim_ac_x11mu_libs $LIBS"

AC_CACHE_CHECK(
  [whether the X11 miscellaneous utilities is available],
  sim_cv_lib_x11mu_avail,
  [AC_TRY_LINK([#include <X11/Xlib.h>
                #include <X11/Xmu/Xmu.h>
                #include <X11/Xmu/StdCmap.h>],
               [(void)XmuAllStandardColormaps(0L);],
               [sim_cv_lib_x11mu_avail=yes],
               [sim_cv_lib_x11mu_avail=no])])

if test x"$sim_cv_lib_x11mu_avail" = xyes; then
  sim_ac_x11mu_avail=yes
  $1
else
  LIBS=$sim_ac_save_libs
  $2
fi
])

# Usage:
#  SIM_AC_CHECK_X11XID([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
#
#  Try to find the X11 extension device library. Sets this
#  shell variable:
#
#    $sim_ac_x11xid_libs   (link libraries the linker needs for X11 XID)
#
#  The LIBS flag will also be modified accordingly. In addition, the
#  variable $sim_ac_x11xid_avail is set to "yes" if the X11 extension
#  device library is found.
#
# Author: Morten Eriksen, <mortene@sim.no>.
#
# TODO:
#    * [mortene:20000122] make sure this work on MSWin (with
#      Cygwin installation)
#

AC_DEFUN([SIM_AC_CHECK_X11XID], [

sim_ac_x11xid_avail=no
sim_ac_x11xid_libs="-lXi"
sim_ac_save_libs=$LIBS
LIBS="$sim_ac_x11xid_libs $LIBS"

AC_CACHE_CHECK(
  [whether the X11 extension device library is available],
  sim_cv_lib_x11xid_avail,
  [AC_TRY_LINK([#include <X11/extensions/XInput.h>],
               [(void)XOpenDevice(0L, 0);],
               [sim_cv_lib_x11xid_avail=yes],
               [sim_cv_lib_x11xid_avail=no])])

if test x"$sim_cv_lib_x11xid_avail" = xyes; then
  sim_ac_x11xid_avail=yes
  $1
else
  LIBS=$sim_ac_save_libs
  $2
fi
])

# Usage:
#  SIM_AC_CHECK_X_INTRINSIC([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
#
#  Try to find the Xt intrinsic library. Sets this shell variable:
#
#    $sim_ac_xt_libs   (link library the linker needs for X Intrinsic)
#
#  The LIBS flag will also be modified accordingly. In addition, the
#  variable $sim_ac_xt_avail is set to "yes" if the X11 Intrinsic
#  library is found.
#
# Author: Morten Eriksen, <mortene@sim.no>.
#

AC_DEFUN([SIM_AC_CHECK_X_INTRINSIC], [

sim_ac_xt_avail=no
sim_ac_xt_libs="-lXt"
sim_ac_save_libs=$LIBS
LIBS="$sim_ac_xt_libs $LIBS"

AC_CACHE_CHECK(
  [whether the X11 Intrinsic library is available],
  sim_cv_lib_xt_avail,
  [AC_TRY_LINK([#include <X11/Intrinsic.h>],
               [(void)XtVaCreateWidget("", 0L, 0L);],
               [sim_cv_lib_xt_avail=yes],
               [sim_cv_lib_xt_avail=no])])

if test x"$sim_cv_lib_xt_avail" = xyes; then
  sim_ac_xt_avail=yes
  $1
else
  LIBS=$sim_ac_save_libs
  $2
fi
])

# Usage:
#   SIM_AC_CHECK_LIBXPM( [ACTION-IF-FOUND], [ACTION-IF-NOT-FOUND] )
#
# Description:
#   This macro checks for libXpm.
#
# Variables:
#   $sim_ac_xpm_avail      yes | no
#   $sim_ac_xpm_libs       [link-line libraries]
#
# Authors:
#   Lars J. Aas <larsa@sim.no>
#

AC_DEFUN([SIM_AC_CHECK_LIBXPM], [

sim_ac_xpm_avail=no
sim_ac_xpm_libs="-lXpm"

AC_CACHE_CHECK(
  [whether libXpm is available],
  sim_cv_lib_xpm_avail,
  [sim_ac_save_libs=$LIBS
  LIBS="$sim_ac_xpm_libs $LIBS"
  AC_TRY_LINK([#include <X11/xpm.h>],
              [(void)XpmLibraryVersion();],
              [sim_cv_lib_xpm_avail=yes],
              [sim_cv_lib_xpm_avail=no])
  LIBS="$sim_ac_save_libs"])

if test x"$sim_cv_lib_xpm_avail" = x"yes"; then
  sim_ac_xpm_avail=yes
  LIBS="$sim_ac_xpm_libs $LIBS"
  $1
else
  ifelse([$2], , :, [$2])
fi
])


# Usage:
#  SIM_AC_CHECK_X11_XP([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
#
#  Try to find the Xp library for printing functionality. Sets this
#  shell variable:
#
#    $sim_ac_xp_libs   (link library the linker needs for the Xp library)
#
#  The LIBS flag will also be modified accordingly. In addition, the
#  variable $sim_ac_xp_avail is set to "yes" if the Xp library is found.
#
# Author: Morten Eriksen, <mortene@sim.no>.
#

AC_DEFUN([SIM_AC_CHECK_X11_XP], [
sim_ac_xp_avail=no
sim_ac_xp_libs="-lXp"
sim_ac_save_libs=$LIBS
LIBS="$sim_ac_xp_libs $LIBS"

AC_CACHE_CHECK(
  [whether the X11 printing library is available],
  sim_cv_lib_xp_avail,
  [AC_TRY_LINK([#include <X11/extensions/Print.h>],
               [XpEndJob(0L);],
               [sim_cv_lib_xp_avail=yes],
               [sim_cv_lib_xp_avail=no])])

if test x"$sim_cv_lib_xp_avail" = xyes; then
  sim_ac_xp_avail=yes
  $1
else
  LIBS=$sim_ac_save_libs
  $2
fi
])

# SIM_AC_CHECK_X11_ATHENA( [ACTION-IF-FOUND], [ACTION-IF-NOT-FOUND] )

AC_DEFUN([SIM_AC_CHECK_X11_ATHENA], [
sim_ac_athena_avail=no
sim_ac_athena_libs="-lXaw"
sim_ac_save_libs=$LIBS
LIBS="$sim_ac_athena_libs $LIBS"

AC_CACHE_CHECK(
  [whether the X11 Athena widgets library is available],
  sim_cv_lib_athena_avail,
  [AC_TRY_LINK([#include <X11/Xfuncproto.h>
                #include <X11/Xaw/XawInit.h>],
               [XawInitializeWidgetSet();],
               [sim_cv_lib_athena_avail=yes],
               [sim_cv_lib_athena_avail=no])])

if test x"$sim_cv_lib_athena_avail" = xyes; then
  sim_ac_athena_avail=yes
  $1
else
  LIBS=$sim_ac_save_libs
  $2
fi
])

# SIM_AC_X11_READY( [ACTION-IF-TRUE], [ACTION-IF-FALSE] )

AC_DEFUN([SIM_AC_CHECK_X11_READY],
[AC_CACHE_CHECK(
  [if X11 linkage is ready],
  [sim_cv_x11_ready],
  [AC_TRY_LINK(
    [#include <X11/Xlib.h>],
    [(void)XOpenDisplay(0L);],
    [sim_cv_x11_ready=true],
    [sim_cv_x11_ready=false])])
if ${sim_cv_x11_ready}; then
  ifelse([$1], , :, [$1])
else
  ifelse([$2], , :, [$2])
fi
]) # SIM_AC_X11_READY()


# **************************************************************************

AC_DEFUN([SIM_AC_HAVE_LIBX11_IFELSE], [
: ${sim_ac_have_libx11=false}
AC_REQUIRE([AC_PATH_X])

# prevent multiple runs
$sim_ac_have_libx11 || {
  if test x"$no_x" != xyes; then
    sim_ac_libx11_cppflags=
    sim_ac_libx11_ldflags=
    test x"$x_includes" != x && sim_ac_libx11_cppflags="-I$x_includes"
    test x"$x_libraries" != x && sim_ac_libx11_ldflags="-L$x_libraries"
    sim_ac_libx11_libs="-lX11"

    sim_ac_libx11_save_cppflags=$CPPFLAGS
    sim_ac_libx11_save_ldflags=$LDFLAGS
    sim_ac_libx11_save_libs=$LIBS

    CPPFLAGS="$CPPFLAGS $sim_ac_libx11_cppflags"
    LDFLAGS="$LDFLAGS $sim_ac_libx11_ldflags"
    LIBS="$sim_ac_libx11_libs $LIBS"

    AC_TRY_LINK(
      [#include <X11/Xlib.h>],
      [(void)XOpenDisplay(0L);],
      [sim_ac_have_libx11=true])

    CPPFLAGS=$sim_ac_libx11_save_cppflags
    LDFLAGS=$sim_ac_libx11_save_ldflags
    LIBS=$sim_ac_libx11_save_libs
  fi
}

if $sim_ac_have_libx11; then
  ifelse([$1], , :, [$1])
else
  ifelse([$2], , :, [$2])
fi
]) # SIM_AC_HAVE_LIBX11_IFELSE


# Usage:
#  SIM_AC_CHECK_OPENGL([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
#
#  Try to find an OpenGL development system, either a native
#  implementation or the OpenGL-compatible Mesa library. If
#  it is found, these shell variables are set:
#
#    $sim_ac_gl_cppflags (extra flags the compiler needs for OpenGL/Mesa)
#    $sim_ac_gl_ldflags  (extra flags the linker needs for OpenGL/Mesa)
#    $sim_ac_gl_libs     (link libraries the linker needs for OpenGL/Mesa)
#
#  The CPPFLAGS, LDFLAGS and LIBS flags will also be modified accordingly.
#  In addition, the variable $sim_ac_gl_avail is set to "yes" if an
#  OpenGL-compatible development system is found.
#
#
# Author: Morten Eriksen, <mortene@sim.no>.

AC_DEFUN(SIM_AC_CHECK_OPENGL, [

unset sim_ac_gl_cppflags
unset sim_ac_gl_ldflags
unset sim_ac_gl_libs
sim_ac_gl_avail=no

AC_ARG_WITH(
  [mesa],
  AC_HELP_STRING([--with-mesa],
                 [prefer MesaGL (if found) over OpenGL [[default=yes]]]),
  [],
  [with_mesa=yes])

# It's usually libGL.so on UNIX systems and opengl32.lib on MSWindows.
sim_ac_gl_glnames="-lGL -lopengl32"
sim_ac_gl_mesaglnames=-lMesaGL

if test "x$with_mesa" = "xyes"; then
  sim_ac_gl_first=$sim_ac_gl_mesaglnames
  sim_ac_gl_second=$sim_ac_gl_glnames
else
  sim_ac_gl_first=$sim_ac_gl_glnames
  sim_ac_gl_second=$sim_ac_gl_mesaglnames
fi

AC_ARG_WITH(
  [opengl],
  AC_HELP_STRING([--with-opengl=DIR],
                 [OpenGL/Mesa installation directory]),
  [],
  [with_opengl=yes])

if test x"$with_opengl" != xno; then
  if test x"$with_opengl" != xyes; then
    sim_ac_gl_cppflags="-I${with_opengl}/include"
    sim_ac_gl_ldflags="-L${with_opengl}/lib"
  else
    # This is a common location for the OpenGL library on HPUX.
    sim_ac_gl_hpux=/opt/graphics/OpenGL
    if test -d $sim_ac_gl_hpux; then
      sim_ac_gl_cppflags=-I$sim_ac_gl_hpux/include
      sim_ac_gl_ldflags=-L$sim_ac_gl_hpux/lib
    fi
  fi

  sim_ac_save_cppflags=$CPPFLAGS
  sim_ac_save_ldflags=$LDFLAGS
  sim_ac_save_libs=$LIBS

  CPPFLAGS="$CPPFLAGS $sim_ac_gl_cppflags"
  LDFLAGS="$LDFLAGS $sim_ac_gl_ldflags"

  AC_CACHE_CHECK(
    [whether OpenGL library is available],
    sim_cv_lib_gl,
    [sim_cv_lib_gl=UNRESOLVED

    for sim_ac_gl_libcheck in $sim_ac_gl_first $sim_ac_gl_second; do
      if test "x$sim_cv_lib_gl" = "xUNRESOLVED"; then
        LIBS="$sim_ac_gl_libcheck $sim_ac_save_libs"
        AC_TRY_LINK([
#if HAVE_WINDOWS_H
#include <windows.h>
#endif /* HAVE_WINDOWS_H */
#include <GL/gl.h>
],
                    [
glPointSize(1.0f);
],
                    [sim_cv_lib_gl="$sim_ac_gl_libcheck"])
      fi
    done
  ])

  LIBS="$sim_ac_save_libs"

  if test "x$sim_cv_lib_gl" != "xUNRESOLVED"; then
    sim_ac_gl_libs="$sim_cv_lib_gl"
  else
    AC_MSG_WARN([couldn't compile or link with OpenGL library -- trying with pthread library in place...])

    SIM_AC_CHECK_PTHREAD([
      sim_ac_gl_cppflags="$sim_ac_gl_cppflags $sim_ac_pthread_cppflags"
      sim_ac_gl_ldflags="$sim_ac_gl_ldflags $sim_ac_pthread_ldflags"],
      [AC_MSG_WARN([couldn't compile or link with pthread library])])

    if test "x$sim_ac_pthread_avail" = "xyes"; then
      AC_CACHE_CHECK(
        [whether OpenGL library can be linked with pthread library],
        sim_cv_lib_gl_pthread,
        [sim_cv_lib_gl_pthread=UNRESOLVED

        for sim_ac_gl_libcheck in $sim_ac_gl_first $sim_ac_gl_second; do
          if test "x$sim_cv_lib_gl_pthread" = "xUNRESOLVED"; then
            LIBS="$sim_ac_gl_libcheck $sim_ac_pthread_libs $sim_ac_save_libs"
            AC_TRY_LINK([
#include <GL/gl.h>
],
                        [
glPointSize(1.0f);
],
                        [sim_cv_lib_gl_pthread="$sim_ac_gl_libcheck"])
          fi
        done
      ])

      if test "x$sim_cv_lib_gl_pthread" != "xUNRESOLVED"; then
        sim_ac_gl_libs="$sim_cv_lib_gl_pthread $sim_ac_pthread_libs"
      fi
    fi
  fi


  if test "x$sim_ac_gl_libs" != "x"; then
    LIBS="$sim_ac_gl_libs $sim_ac_save_libs"
    sim_ac_gl_avail=yes
    $1
  else
    CPPFLAGS=$sim_ac_save_cppflags
    LDFLAGS=$sim_ac_save_ldflags
    LIBS=$sim_ac_save_libs
    $2
  fi
fi
])


# Usage:
#  SIM_AC_CHECK_GLU([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
#
#  Try to use the OpenGL utility library; GLU. If it is found,
#  these shell variables are set:
#
#    $sim_ac_glu_cppflags (extra flags the compiler needs for GLU)
#    $sim_ac_glu_ldflags  (extra flags the linker needs for GLU)
#    $sim_ac_glu_libs     (link libraries the linker needs for GLU)
#
#  The CPPFLAGS, LDFLAGS and LIBS flags will also be modified accordingly.
#  In addition, the variable $sim_ac_gly_avail is set to "yes" if GLU
#  is found.
#
#
# Author: Morten Eriksen, <mortene@sim.no>.

AC_DEFUN(SIM_AC_CHECK_GLU, [

unset sim_ac_glu_cppflags
unset sim_ac_glu_ldflags
unset sim_ac_glu_libs
sim_ac_glu_avail=no

# It's usually libGLU.so on UNIX systems and glu32.lib on MSWindows.
sim_ac_glu_names="-lGLU -lglu32"
sim_ac_glu_mesanames=-lMesaGLU

# with_mesa is set from the SIM_AC_CHECK_OPENGL macro.
if test "x$with_mesa" = "xyes"; then
  sim_ac_glu_first=$sim_ac_glu_mesanames
  sim_ac_glu_second=$sim_ac_glu_names
else
  sim_ac_glu_first=$sim_ac_glu_names
  sim_ac_glu_second=$sim_ac_glu_mesanames
fi

AC_ARG_WITH(
  [glu],
  AC_HELP_STRING([--with-glu=DIR],
                 [use the OpenGL utility library [[default=yes]]]),
  [],
  [with_glu=yes])

if test x"$with_glu" != xno; then
  if test x"$with_glu" != xyes; then
    sim_ac_glu_cppflags="-I${with_glu}/include"
    sim_ac_glu_ldflags="-L${with_glu}/lib"
  fi

  sim_ac_save_cppflags=$CPPFLAGS
  sim_ac_save_ldflags=$LDFLAGS
  sim_ac_save_libs=$LIBS

  CPPFLAGS="$CPPFLAGS $sim_ac_glu_cppflags"
  LDFLAGS="$LDFLAGS $sim_ac_glu_ldflags"

  AC_CACHE_CHECK(
    [whether GLU is available],
    sim_cv_lib_glu,
    [sim_cv_lib_glu=UNRESOLVED

    # Some platforms (like BeOS) have the GLU functionality in the GL
    # library (and no GLU library present).
    for sim_ac_glu_libcheck in "" $sim_ac_glu_first $sim_ac_glu_second; do
      if test "x$sim_cv_lib_glu" = "xUNRESOLVED"; then
        LIBS="$sim_ac_glu_libcheck $sim_ac_save_libs"
        AC_TRY_LINK([
#if HAVE_WINDOWS_H
#include <windows.h>
#endif /* HAVE_WINDOWS_H */
#include <GL/gl.h>
#include <GL/glu.h>
],
                    [
gluSphere(0L, 1.0, 1, 1);
],
                    [sim_cv_lib_glu="$sim_ac_glu_libcheck"])
      fi
    done
  ])

  LIBS="$sim_ac_save_libs"

  if test "x$sim_cv_lib_glu" != "xUNRESOLVED"; then
    sim_ac_glu_libs="$sim_cv_lib_glu"
    LIBS="$sim_ac_glu_libs $sim_ac_save_libs"
    sim_ac_glu_avail=yes
    $1
  else
    CPPFLAGS=$sim_ac_save_cppflags
    LDFLAGS=$sim_ac_save_ldflags
    LIBS=$sim_ac_save_libs
    $2
  fi
fi
])


# **************************************************************************
# SIM_AC_GLU_READY_IFELSE( [ACTION-IF-TRUE], [ACTION-IF-FALSE] )

AC_DEFUN([SIM_AC_GLU_READY_IFELSE],
[AC_CACHE_CHECK(
  [if GLU is available as part of GL library],
  [sim_cv_glu_ready],
  [AC_TRY_LINK(
    [
#if HAVE_WINDOWS_H
#include <windows.h>
#endif /* HAVE_WINDOWS_H */
#include <GL/gl.h>
#include <GL/glu.h>
],
    [
gluSphere(0L, 1.0, 1, 1);
],
    [sim_cv_glu_ready=true],
    [sim_cv_glu_ready=false])])
if ${sim_cv_glu_ready}; then
  ifelse([$1], , :, [$1])
else
  ifelse([$2], , :, [$2])
fi
]) # SIM_AC_GLU_READY_IFELSE()


# Usage:
#  SIM_AC_GLU_NURBSOBJECT([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
#
#  Try to find out whether the interface struct against the GLU
#  library NURBS functions is called "GLUnurbs" or "GLUnurbsObj".
#  (This seems to have changed somewhere between release 1.1 and
#  release 1.3 of GLU).
#
#  The variable $sim_ac_glu_nurbsobject is set to the correct name
#  if the nurbs structure is found.
#
# Author: Morten Eriksen, <mortene@sim.no>.

AC_DEFUN(SIM_AC_GLU_NURBSOBJECT, [
AC_CACHE_CHECK(
  [what structure to use in the GLU NURBS interface],
  sim_cv_func_glu_nurbsobject,
  [sim_cv_func_glu_nurbsobject=NONE
   for sim_ac_glu_structname in GLUnurbs GLUnurbsObj; do
    if test "$sim_cv_func_glu_nurbsobject" = NONE; then
      AC_TRY_LINK([
#if HAVE_WINDOWS_H
#include <windows.h>
#endif /* HAVE_WINDOWS_H */
#include <GL/gl.h>
#include <GL/glu.h>],
                  [$sim_ac_glu_structname * hepp = gluNewNurbsRenderer();
                   gluDeleteNurbsRenderer(hepp)],
                  [sim_cv_func_glu_nurbsobject=$sim_ac_glu_structname])
    fi
  done
])

if test $sim_cv_func_glu_nurbsobject = NONE; then
  sim_ac_glu_nurbsobject=
  $2
else
  sim_ac_glu_nurbsobject=$sim_cv_func_glu_nurbsobject
  $1
fi
])

# **************************************************************************
# SIM_AC_HAVE_GLX_IFELSE( IF-FOUND, IF-NOT-FOUND )
#
# Check whether GLX is on the system.

AC_DEFUN([SIM_AC_HAVE_GLX_IFELSE], [
AC_CACHE_CHECK(
  [whether GLX is on the system],
  sim_cv_have_glx,
  AC_TRY_LINK(
    [#include <GL/glx.h>],
    [(void)glXChooseVisual(0L, 0, 0L);],
    [sim_cv_have_glx=true],
    [sim_cv_have_glx=false]))

if ${sim_cv_have_glx=false}; then
  ifelse([$1], , :, [$1])
else
  ifelse([$2], , :, [$2])
fi
]) # SIM_AC_HAVE_GLX_IFELSE()


# Usage:
#  SIM_AC_CHECK_PTHREAD([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
#
#  Try to find the PTHREAD development system. If it is found, these
#  shell variables are set:
#
#    $sim_ac_pthread_cppflags (extra flags the compiler needs for pthread)
#    $sim_ac_pthread_ldflags  (extra flags the linker needs for pthread)
#    $sim_ac_pthread_libs     (link libraries the linker needs for pthread)
#
#  The CPPFLAGS, LDFLAGS and LIBS flags will also be modified accordingly.
#  In addition, the variable $sim_ac_pthread_avail is set to "yes" if the
#  pthread development system is found.
#
#
# Author: Morten Eriksen, <mortene@sim.no>.

AC_DEFUN([SIM_AC_CHECK_PTHREAD], [

AC_ARG_WITH(
  [pthread],
  AC_HELP_STRING([--with-pthread=DIR],
                 [pthread installation directory]),
  [],
  [with_pthread=yes])

sim_ac_pthread_avail=no

if test x"$with_pthread" != xno; then
  if test x"$with_pthread" != xyes; then
    sim_ac_pthread_cppflags="-I${with_pthread}/include"
    sim_ac_pthread_ldflags="-L${with_pthread}/lib"
  fi
  sim_ac_pthread_libs="-lpthread"

  sim_ac_save_cppflags=$CPPFLAGS
  sim_ac_save_ldflags=$LDFLAGS
  sim_ac_save_libs=$LIBS

  CPPFLAGS="$CPPFLAGS $sim_ac_pthread_cppflags"
  LDFLAGS="$LDFLAGS $sim_ac_pthread_ldflags"
  LIBS="$sim_ac_pthread_libs $LIBS"

  AC_CACHE_CHECK(
    [whether the pthread development system is available],
    sim_cv_lib_pthread_avail,
    [AC_TRY_LINK([#include <pthread.h>],
                 [(void)pthread_create(0L, 0L, 0L, 0L);],
                 [sim_cv_lib_pthread_avail=yes],
                 [sim_cv_lib_pthread_avail=no])])

  if test x"$sim_cv_lib_pthread_avail" = xyes; then
    sim_ac_pthread_avail=yes
    $1
  else
    CPPFLAGS=$sim_ac_save_cppflags
    LDFLAGS=$sim_ac_save_ldflags
    LIBS=$sim_ac_save_libs
    $2
  fi
fi
])


# Usage:
#  SIM_CHECK_OIV_XT([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
#
#  Try to compile and link against the Xt GUI glue library for
#  the Open Inventor development system. Sets this shell
#  variable:
#
#    $sim_ac_oivxt_libs     (link libraries the linker needs for InventorXt)
#
#  The LIBS variable will also be modified accordingly. In addition,
#  the variable $sim_ac_oivxt_avail is set to "yes" if the Xt glue
#  library for the Open Inventor development system is found.
#
# Author: Morten Eriksen, <mortene@sim.no>.
#

AC_DEFUN([SIM_CHECK_OIV_XT], [
sim_ac_oivxt_avail=no

sim_ac_oivxt_libs="-lInventorXt"
sim_ac_save_libs=$LIBS
LIBS="$sim_ac_oivxt_libs $LIBS"

AC_CACHE_CHECK([for Xt glue library in the Open Inventor developer kit],
  sim_cv_lib_oivxt_avail,
  [AC_TRY_LINK([#include <Inventor/Xt/SoXt.h>],
               [(void)SoXt::init(0L, 0L);],
               [sim_cv_lib_oivxt_avail=yes],
               [sim_cv_lib_oivxt_avail=no])])

if test x"$sim_cv_lib_oivxt_avail" = xyes; then
  sim_ac_oivxt_avail=yes
  $1
else
  LIBS=$sim_ac_save_libs
  $2
fi
])

# **************************************************************************
# SIM_AC_WITH_INVENTOR
# This macro just ensures the --with-inventor option is used.

AC_DEFUN([SIM_AC_WITH_INVENTOR], [
: ${sim_ac_want_inventor=false}
AC_ARG_WITH([inventor],
  AC_HELP_STRING([--with-inventor], [use another Open Inventor than Coin [[default=no]]])
AC_HELP_STRING([--with-inventor=PATH], [specify where Open Inventor resides]),
  [case "$withval" in
  no)  sim_ac_want_inventor=false ;;
  yes) sim_ac_want_inventor=true
       test -n "$OIVHOME" &&
         SIM_AC_DEBACKSLASH(sim_ac_inventor_path, "$OIVHOME") ;;
  *)   sim_ac_want_inventor=true; sim_ac_inventor_path="$withval" ;;
  esac])
]) # SIM_AC_WITH_INVENTOR

# **************************************************************************
# SIM_AC_HAVE_INVENTOR_IMAGE_IFELSE

AC_DEFUN([SIM_AC_HAVE_INVENTOR_IMAGE_IFELSE], [
AC_REQUIRE([SIM_AC_WITH_INVENTOR])

if $sim_ac_want_inventor; then
  sim_ac_inventor_image_save_CPPFLAGS="$CPPFLAGS"
  sim_ac_inventor_image_save_LDFLAGS="$LDFLAGS"
  sim_ac_inventor_image_save_LIBS="$LIBS"

  if test s${sim_ac_inventor_path+et} = set; then
    sim_ac_inventor_image_cppflags="-I${sim_ac_inventor_path}/include"
    sim_ac_inventor_image_ldflags="-L${sim_ac_inventor_path}/lib"
  fi
  sim_ac_inventor_image_libs="-limage"

  AC_CACHE_CHECK(
    [if linking with libimage is possible],
    sim_cv_have_inventor_image,
    [
    CPPFLAGS="$sim_ac_inventor_image_cppflags $CPPFLAGS"
    LDFLAGS="$sim_ac_inventor_image_ldflags $LDFLAGS"
    LIBS="$sim_ac_inventor_image_libs $LIBS"
    AC_TRY_LINK(
      [],
      [],
      [sim_cv_have_inventor_image=true],
      [sim_cv_have_inventor_image=false])
    CPPFLAGS="$sim_ac_inventor_image_save_CPPFLAGS"
    LDFLAGS="$sim_ac_inventor_image_save_LDFLAGS"
    LIBS="$sim_ac_inventor_image_save_LIBS"
    ])

  if $sim_cv_have_inventor_image; then
    ifelse([$1], , :, [$1])
  else
    ifelse([$2], , :, [$2])
  fi
else
  ifelse([$2], , :, [$2])
fi
]) # SIM_AC_HAVE_INVENTOR_IMAGE_IFELSE

# **************************************************************************
# SIM_AC_HAVE_INVENTOR_IFELSE( [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND] ] )
#
# Defines $sim_ac_inventor_cppflags, $sim_ac_inventor_ldflags and
# $sim_ac_inventor_libs.

AC_DEFUN([SIM_AC_HAVE_INVENTOR_IFELSE], [
AC_REQUIRE([SIM_AC_WITH_INVENTOR])

if $sim_ac_want_inventor; then
  sim_ac_save_CPPFLAGS="$CPPFLAGS";
  sim_ac_save_LDFLAGS="$LDFLAGS";
  sim_ac_save_LIBS="$LIBS";

  SIM_AC_HAVE_INVENTOR_IMAGE_IFELSE([
    sim_ac_inventor_cppflags="$sim_ac_inventor_image_cppflags"
    sim_ac_inventor_ldflags="$sim_ac_inventor_image_ldflags"
  ], [
    if test s${sim_ac_inventor_path+et} = set; then
      sim_ac_inventor_cppflags="-I${sim_ac_inventor_path}/include"
      sim_ac_inventor_ldflags="-L${sim_ac_inventor_path}/lib"
    fi
    sim_ac_inventor_image_libs=
  ])

  # Let's at least test for "libInventor".
  sim_ac_inventor_chk_libs="-lInventor"

  # See if we can get the TGS_VERSION number for including a
  # check for inv{ver}.lib.
    cat <<EOF > conftest.c
#include <Inventor/SbBasic.h>
PeekInventorVersion: TGS_VERSION
EOF
  tgs_version=`$CPP $sim_ac_inventor_cppflags $CPPFLAGS conftest.c 2>/dev/null | grep "^PeekInventorVersion" | sed 's/.* //g'`
  rm -f conftest.c
  if test x"$tgs_version" != xTGS_VERSION; then
    tgs_version=`echo $tgs_version | cut -c-3`
    sim_ac_inventor_chk_libs="$sim_ac_inventor_chk_libs -linv${tgs_version}"
  fi

  AC_MSG_CHECKING([for Open Inventor library])
  sim_ac_inventor_libs=UNRESOLVED

  for sim_ac_iv_cppflags_loop in "" "-DWIN32"; do
    for sim_ac_iv_libcheck in $sim_ac_inventor_chk_libs; do
      if test "x$sim_ac_inventor_libs" = "xUNRESOLVED"; then
        CPPFLAGS="$sim_ac_iv_cppflags_loop $sim_ac_inventor_cppflags $sim_ac_save_CPPFLAGS"
        LDFLAGS="$sim_ac_inventor_ldflags $sim_ac_save_LDFLAGS"
        LIBS="$sim_ac_iv_libcheck $sim_ac_inventor_image_libs $sim_ac_save_LIBS"
        AC_TRY_LINK([#include <Inventor/SoDB.h>],
                    [SoDB::init();],
                    [sim_ac_inventor_libs="$sim_ac_iv_libcheck $sim_ac_inventor_image_libs"
                     sim_ac_inventor_cppflags="$sim_ac_iv_cppflags_loop $sim_ac_inventor_cppflags"])
      fi
    done
  done

  CPPFLAGS="$sim_ac_save_CPPFLAGS"
  LDFLAGS="$sim_ac_save_LDFLAGS"
  LIBS="$sim_ac_save_LIBS"

  if test "x$sim_ac_inventor_libs" != "xUNRESOLVED"; then
    AC_MSG_RESULT($sim_ac_inventor_cppflags $sim_ac_inventor_ldflags $sim_ac_inventor_libs)
    $1
  else
    AC_MSG_RESULT([unavailable])
    $2
  fi
else
  ifelse([$2], , :, [$2])
fi
]) # SIM_AC_HAVE_INVENTOR_IFELSE

# **************************************************************************

# utility macros:
AC_DEFUN([AC_TOUPPER], [translit([$1], [[a-z]], [[A-Z]])])
AC_DEFUN([AC_TOLOWER], [translit([$1], [[A-Z]], [[a-z]])])

# **************************************************************************
# SIM_AC_HAVE_INVENTOR_NODE( NODE, [ACTION-IF-FOUND] [, ACTION-IF-NOT-FOUND])
#
# Check whether or not the given NODE is available in the Open Inventor
# development system.  If so, the HAVE_<NODE> define is set.
#
# Authors:
#   Lars J. Aas  <larsa@sim.no>
#   Morten Eriksen  <mortene@sim.no>

AC_DEFUN([SIM_AC_HAVE_INVENTOR_NODE], 
[m4_do([pushdef([cache_variable], sim_cv_have_oiv_[]AC_TOLOWER([$1])_node)],
       [pushdef([DEFINE_VARIABLE], HAVE_[]AC_TOUPPER([$1]))])
AC_CACHE_CHECK(
  [if the Open Inventor $1 node is available],
  cache_variable,
  [AC_TRY_LINK(
    [#include <Inventor/nodes/$1.h>],
    [$1 * p = new $1;],
    cache_variable=true,
    cache_variable=false)])

if $cache_variable; then
  AC_DEFINE(DEFINE_VARIABLE, 1, [Define to enable use of the Open Inventor $1 node])
  $2
else
  ifelse([$3], , :, [$3])
fi
m4_do([popdef([cache_variable])],
      [popdef([DEFINE_VARIABLE])])
]) # SIM_AC_HAVE_INVENTOR_NODE

# **************************************************************************
# SIM_AC_HAVE_INVENTOR_FEATURE(MESSAGE, HEADERS, BODY, DEFINE
#                              [, ACTION-IF-FOUND[, ACTION-IF-NOT-FOUND]])
#
# Authors:
#   Morten Eriksen <mortene@sim.no>

AC_DEFUN([SIM_AC_HAVE_INVENTOR_FEATURE],
[m4_do([pushdef([cache_variable], sim_cv_have_oiv_[]AC_TOLOWER([$4]))],
       [pushdef([DEFINE_VARIABLE], AC_TOUPPER([$4]))])
AC_CACHE_CHECK(
  [$1],
  cache_variable,
  [AC_TRY_LINK(
    [$2],
    [$3],
    cache_variable=true,
    cache_variable=false)])

if $cache_variable; then
  AC_DEFINE(DEFINE_VARIABLE, 1, [Define to enable use of Inventor feature])
  $5
else
  ifelse([$6], , :, [$6])
fi
m4_do([popdef([cache_variable])],
      [popdef([DEFINE_VARIABLE])])
]) # SIM_AC_HAVE_INVENTOR_FEATURE


# Convenience macros SIM_AC_DEBACKSLASH and SIM_AC_DOBACKSLASH for
# converting to and from MSWin/MS-DOS style paths.
#
# Example use:
#
#     SIM_AC_DEBACKSLASH(my_ac_reversed, "C:\\mydir\\bin")
#
# will give a shell variable $my_ac_reversed with the value "C:/mydir/bin").
# Vice versa for SIM_AC_DOBACKSLASH.
#
# Author: Marius Bugge Monsen <mariusbu@sim.no>
#         Lars J�rgen Aas <larsa@sim.no>
#         Morten Eriksen <mortene@sim.no>

AC_DEFUN([SIM_AC_DEBACKSLASH], [
eval "$1=\"`echo $2 | sed -e 's%\\\\%\\/%g'`\""
])

AC_DEFUN([SIM_AC_DOBACKSLASH], [
eval "$1=\"`echo $2 | sed -e 's%\\/%\\\\%g'`\""
])

AC_DEFUN([SIM_AC_DODOUBLEBACKSLASH], [
eval "$1=\"`echo $2 | sed -e 's%\\/%\\\\\\\\\\\\\\\\%g'`\""
])


# Usage:
#  SIM_CHECK_MOTIF([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
#
#  Try to compile and link against the Motif library. Sets these
#  shell variables:
#
#    $sim_ac_motif_cppflags (extra flags the compiler needs for Motif)
#    $sim_ac_motif_ldflags  (extra flags the linker needs for Motif)
#    $sim_ac_motif_libs     (link libraries the linker needs for Motif)
#
#  The CPPFLAGS, LDFLAGS and LIBS flags will also be modified accordingly.
#  In addition, the variable $sim_ac_motif_avail is set to "yes" if
#  the Motif library development installation is ok.
#
# Author: Morten Eriksen, <mortene@sim.no>.
#

AC_DEFUN([SIM_CHECK_MOTIF], [
AC_PREREQ([2.14.1])

AC_ARG_WITH(
  [motif],
  AC_HELP_STRING([--with-motif=DIR],
                 [use the Motif library [default=yes]]),
  [],
  [with_motif=yes])

sim_ac_motif_avail=no

if test x"$with_motif" != xno; then
  if test x"$with_motif" != xyes; then
    sim_ac_motif_cppflags="-I${with_motif}/include"
    sim_ac_motif_ldflags="-L${with_motif}/lib"
  fi

  sim_ac_motif_libs="-lXm"

  sim_ac_save_cppflags=$CPPFLAGS
  sim_ac_save_ldflags=$LDFLAGS
  sim_ac_save_libs=$LIBS

  CPPFLAGS="$sim_ac_motif_cppflags $CPPFLAGS"
  LDFLAGS="$sim_ac_motif_ldflags $LDFLAGS"
  LIBS="$sim_ac_motif_libs $LIBS"

  AC_CACHE_CHECK(
    [for a Motif development environment],
    sim_cv_lib_motif_avail,
    [AC_TRY_LINK([#include <Xm/Xm.h>],
                 [XmUpdateDisplay(0L);],
                 [sim_cv_lib_motif_avail=yes],
                 [sim_cv_lib_motif_avail=no])])

  if test x"$sim_cv_lib_motif_avail" = xyes; then
    sim_ac_motif_avail=yes
    $1
  else
    CPPFLAGS=$sim_ac_save_cppflags
    LDFLAGS=$sim_ac_save_ldflags
    LIBS=$sim_ac_save_libs
    $2
  fi
fi
])

# Usage:
#  SIM_CHECK_XMEDRAWSHADOWS([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
#
#  Try to compile and link code with the XmeDrawShadows() function
#  from Motif 2.0 (which is used by the InventorXt library). Sets the
#  variable $sim_ac_xmedrawshadows_avail to either "yes" or "no".
#
#
# Author: Morten Eriksen, <mortene@sim.no>.
#

AC_DEFUN([SIM_CHECK_XMEDRAWSHADOWS], [
AC_PREREQ([2.14.1])

sim_ac_xmedrawshadows_avail=no

AC_CACHE_CHECK(
  [for XmeDrawShadows() function in Motif library],
  sim_cv_lib_xmedrawshadows_avail,
  [AC_TRY_LINK([#include <Xm/Xm.h>],
               [XmeDrawShadows(0L, 0L, 0L, 0L, 0, 0, 0, 0, 0, 0);],
               [sim_cv_lib_xmedrawshadows_avail=yes],
               [sim_cv_lib_xmedrawshadows_avail=no])])

if test x"$sim_cv_lib_xmedrawshadows_avail" = xyes; then
  sim_ac_xmedrawshadows_avail=yes
  $1
else
  ifelse([$2], , :, [$2])
fi
])

# Usage:
#   SIM_CHECK_MOTIF_GLWIDGET([ ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND ]])
#
# Description:
#   This macro checks for a GL widget that can be used with Xt/Motif.
#  
# Variables:
#   $sim_cv_motif_glwidget         (cached)  class + header + library
#   $sim_cv_motif_glwidget_hdrloc  (cached)  GL | X11/GLw
#
#   $sim_ac_motif_glwidget_class             glwMDrawingAreaWidgetClass |
#                                            glwDrawingAreaWidgetClass
#   $sim_ac_motif_glwidget_header            GLwDrawA.h | GLwMDrawA.h
#   $sim_ac_motif_glwidget_library           GLwM | GLw | MesaGLwM | MesaGLw
#  
#   $LIBS = -l$sim_ac_motif_glwidget_library $LIBS
#  
# Defines:
#   XT_GLWIDGET                              $sim_ac_motif_glwidget_class
#   HAVE_GL_GLWDRAWA_H                       #include <GL/GLwDrawA.h>
#   HAVE_GL_GLWMDRAWA_H                      #include <GL/GLwMDrawA.h>
#   HAVE_X11_GWL_GLWDRAWA_H                  #include <X11/GLw/GLwDrawA.h>
#   HAVE_X11_GWL_GLWMDRAWA_H                 #include <X11/GLw/GLwMDrawA.h>
#  
# Authors:
#   Lars J. Aas <larsa@sim.no>,
#   Loring Holden <lsh@cs.brown.edu>,
#   Morten Eriksen <mortene@sim.no>
#  

AC_DEFUN([SIM_CHECK_MOTIF_GLWIDGET], [

AC_CACHE_CHECK(
  [for a GL widget],
  sim_cv_motif_glwidget,
  [SAVELIBS=$LIBS
  sim_cv_motif_glwidget=UNKNOWN
  for lib in GLwM GLw MesaGLwM MesaGLw; do
    if test x"$sim_cv_motif_glwidget" = x"UNKNOWN"; then
      LIBS="-l$lib $SAVELIBS"
      AC_TRY_LINK(
        [#include <X11/Intrinsic.h>
        extern WidgetClass glwMDrawingAreaWidgetClass;],
        [Widget glxManager = NULL;
        Widget glxWidget = XtVaCreateManagedWidget("GLWidget",
          glwMDrawingAreaWidgetClass, glxManager, NULL);],
        [sim_cv_motif_glwidget="glwMDrawingAreaWidgetClass GLwMDrawA.h $lib"],
        [sim_cv_motif_glwidget=UNKNOWN])
    fi
    if test x"$sim_cv_motif_glwidget" = x"UNKNOWN"; then
      LIBS="-l$lib $SAVELIBS"
      AC_TRY_LINK(
        [#include <X11/Intrinsic.h>
        extern WidgetClass glwDrawingAreaWidgetClass;],
        [Widget glxManager = NULL;
        Widget glxWidget = XtVaCreateManagedWidget("GLWidget",
          glwDrawingAreaWidgetClass, glxManager, NULL);],
        [sim_cv_motif_glwidget="glwDrawingAreaWidgetClass GLwDrawA.h $lib"],
        [sim_cv_motif_glwidget=UNKNOWN])
    fi
  done
  LIBS=$SAVELIBS
  ])

if test "x$sim_cv_motif_glwidget" = "xUNKNOWN"; then
  ifelse([$2], , :, [$2])
else
  sim_ac_motif_glwidget_class=`echo $sim_cv_motif_glwidget | cut -d" " -f1`
  sim_ac_motif_glwidget_header=`echo $sim_cv_motif_glwidget | cut -d" " -f2`
  sim_ac_motif_glwidget_library=`echo $sim_cv_motif_glwidget | cut -d" " -f3`

  AC_CACHE_CHECK(
    [the $sim_ac_motif_glwidget_header header location],
    sim_cv_motif_glwidget_hdrloc,
    [sim_cv_motif_glwidget_hdrloc=UNKNOWN
    for location in X11/GLw GL; do
      if test "x$sim_cv_motif_glwidget_hdrloc" = "xUNKNOWN"; then
        AC_TRY_CPP(
          [#include <X11/Intrinsic.h>
          #include <$location/$sim_ac_motif_glwidget_header>],
          [sim_cv_motif_glwidget_hdrloc=$location],
          [sim_cv_motif_glwidget_hdrloc=UNKNOWN])
      fi
    done])

  if test "x$sim_cv_motif_glwidget_hdrloc" = "xUNKNOWN"; then
    ifelse([$2], , :, [$2])
  else
    if test "x$sim_ac_motif_glwidget_header" = "xGLwDrawA.h"; then
      if test "x$sim_cv_motif_glwidget_hdrloc" = "xGL"; then
        AC_DEFINE(HAVE_GL_GLWDRAWA_H, 1,
          [Define this to use OpenGL widget from <GL/GLwDrawA.h>])
      else
        AC_DEFINE(HAVE_X11_GLW_GLWDRAWA_H, 1,
          [Define this to use OpenGL widget from <X11/GLw/GLwDrawA.h>])
      fi
    else
      if test "x$sim_cv_motif_glwidget_hdrloc" = "xGL"; then
        AC_DEFINE(HAVE_GL_GLWMDRAWA_H, 1,
          [Define this to use OpenGL widget from <GL/GLwMDrawA.h>])
      else
        AC_DEFINE(HAVE_X11_GLW_GLWMDRAWA_H, 1,
          [Define this to use OpenGL widget from <X11/GLw/GLwMDrawA.h>])
      fi
    fi

    AC_DEFINE_UNQUOTED(XT_GLWIDGET, $sim_ac_motif_glwidget_class,
      [Define this to the Xt/Motif OpenGL widget class to use])

    LIBS="-l$sim_ac_motif_glwidget_library $LIBS"

    $1
  fi
fi
])


