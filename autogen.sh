#! /bin/sh

############################################################################
# Regenerate all files which are constructed by the autoconf, automake and
# libtool tool-chain. Note: only developers should need to use this script.

# Authors:
#   Morten Eriksen, <mortene@sim.no>.
#   Lars J. Aas, <larsa@sim.no>.

DIE=false

AUTOCONF_VER=2.14a   # Autoconf from CVS
AUTOMAKE_VER=1.4a    # Automake from CVS
LIBTOOL_VER=1.3.5

MACRODIR=conf-macros
AUTOMAKE_ADD=

echo "Checking the installed configuration tools..."

if test -z "`autoconf --version | grep \" $AUTOCONF_VER\" 2> /dev/null`"; then
  cat <<EOF

  Invalid Version of Autoconf
  ---------------------------
  You must use the CVS development version of Autoconf ($AUTOCONF_VER)
  to generate configure information and Makefiles for $PROJECT.

  The CVS autoconf repository can be fetched by running the following
  set of commands:

  $ cvs -d :pserver:anoncvs@subversions.gnu.org:/cvs login
    (no password)
  $ cvs -d :pserver:anoncvs@subversions.gnu.org:/cvs co autoconf

EOF
  DIE=true
fi

if test -z "`automake --version | grep \" $AUTOMAKE_VER\" 2> /dev/null`"; then
  cat <<EOF

  Invalid Version of Automake
  ---------------------------
  You must use the CVS development version of automake ($AUTOMAKE_VER)
  to generate configure information and Makefiles for $PROJECT.

  The CVS autoconf repository can be fetched by running the following
  set of commands:

  $ cvs -d :pserver:anoncvs@subversions.gnu.org:/cvs/automake login
    (no password)
  $ cvs -d :pserver:anoncvs@subversions.gnu.org:/cvs/automake co autoconf

EOF
  DIE=true
fi

if test -z "`libtool --version | egrep \"$LIBTOOL_VER\" 2> /dev/null`"; then
  cat <<EOF

  Invalid Version of Libtool
  --------------------------
  You must have libtool version $LIBTOOL_VER installed to generate
  configure information and Makefiles for $PROJECT.

  Get ftp://ftp.gnu.org/pub/gnu/libtool/libtool-1.3.5.tar.gz

EOF
    DIE=true
fi

$DIE && exit 1

echo "Running aclocal (generating aclocal.m4)..."
aclocal -I $MACRODIR

echo "Running autoheader (generating config.h.in)..."
autoheader

echo "Running automake (generating the Makefile.in files)..."
automake --foreign $AUTOMAKE_ADD

AMBUGFIXES=`find . -name Makefile.in.diff`
fixmsg=0
for bugfix in $AMBUGFIXES; do
  if test $fixmsg -eq 0; then
    echo "[correcting automake bugs]"
    fixmsg=1
  fi
  patch -p0 < $bugfix
done

echo "Running autoconf (generating ./configure)..."
autoconf

echo "Done."

