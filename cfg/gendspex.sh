#!/usr/bin/bash
# **************************************************************************
# This script generats a Microsoft Developer Studio project
# and workspace files (.dsp/.dsw) for simple projects. It hooks into
# the Automake process as a fake compiler, building the project file
# instead of the sources.
#
# Authors:
#   Thomas Hammer <thammer@sim.no>
#   Lars J. Aas <larsa@coin3d.org> (wrote the original gendsp.sh script)
#
#
# Todo:
# - add vc7 templates
#

me=$0
# run this where needed: me=`echo $me | sed 's%^.*/%%g'`

sourcefile=
objectfile=
dependfile=
outputfile=
sourcefiles=
debuglibfiles=
releaselibfiles=
defines=
libdirs=
includedirs=

workspace_template=
project_tamplate_main=
project_template_source=
sourcedir=
substitutes=

function abs2dots ()
{
  # usage: abs2dots <basedir> <subdir> [delimiter]
  #
  #        computes relative path from subdir to basedir
  #        if subdir is a subdirectory of basedir
  #
  # ex   : abs2dots /some/dir /some/dir/and/sub /
  #        would echo: "../.."

  if test x"$1" = x"$2"; then
    echo "."
    return 0
  fi

  local delimiter="/"
  if ! test x"$3" = x""; then
    delimiter=$3
  fi

  local baselen=`echo "$1"|wc -c | sed -e "s% %%g"`
  local subbase=`echo $2 | cut -c-$((baselen-1))`

  if ! test x"$1" = x"$subbase"; then
    return -1
  fi

  local subrest=`echo $2 | cut -c$((baselen+1))-`
  local dots=`echo $subrest | sed -e "s%[^$delimiter]*%..%g"`

  echo $dots;
  return 0
}

function issubdir ()
{
  # usage: issubdir <basedir> <subdir>
  #

  local basedir=$1
  local subdir=$2
  local curdir=`pwd`
  if test -d $1; then cd $1; basedir=`pwd`; cd "$curdir"; fi
  if test -d $2; then cd $2; subdir=`pwd`; cd "$curdir"; fi

  if test x"$basedir" = x"$subdir"; then
    return 0
  fi

  local baselen=`echo "$basedir"|wc -c | sed -e "s% %%g"`
  local subbase=`echo $subdir | cut -c-$((baselen-1))`

  if ! test x"$basedir" = x"$subbase"; then
    return -1
  fi

  return 0
}

function substitute_dir ()
{
  # usage: substitute_dir <dir>
  #
  # filter dir with substitutelist
  # convert to windows-style directory
  #
  local value=$1
  local substitute=
  local from=
  local to=
  for substitute in $substitutes; do
    to=`echo $substitute | cut -d= -f1`
    from=`echo $substitute | cut -d= -f2`
    value=`echo $value | sed -e "s%$from%$to%g"`
  done

  local curdir=`pwd`
  local wvalue=`cygpath -w $value`
  local wcurdir=`cygpath -w $curdir`
  local wvalue2=`abs2dots $wvalue $wcurdir \\\\`
  if ! test x"$wvalue2" = x""; then
    wvalue=$wvalue2
  fi
  echo "$wvalue"
}

for arg
do
  if test x"$outputfile" = x"next"; then
    outputfile=$arg
  else
    case $arg in
    -c )
      # -c only means _compile_ some file, not that the source file is
      # the next argument, hence we need to do it differently than for
      # the -o option
      sourcefile=get
      ;;
    -o ) outputfile=next ;;
    -MF | -MD | -MP )
      # haven't investigated if one of these are defined to be last
      # before the dep-file, so i've done it this way.
      dependfile=get
      ;;
    -Wp,-MD,* )
      dependfile=`echo $arg | cut -c9-`
      ;;
    -Dsourcedir=* )
      sourcedir=`echo $arg | cut -d= -f2-`
      ;;
    -Dtemplatesuffix=* )
      suffix=`echo $arg | cut -d= -f2-`
      workspace_template="workspace_template_$suffix.txt"
      project_template_main="project_template_main_$suffix.txt"
      project_template_source="project_template_source_$suffix.txt"
      ;;
    -Dsubstitutes=* )
      substitutes=`echo $arg | cut -d= -f2- | sed -e 's%,% %g'`
      ;;
    -l* )
      value=`echo $arg | cut -c3-`
      releaselibfiles="$releaselibfiles $value.lib"
      # add "d" suffix to use debug version of coin/sowin/soqt
      debuglibs="coin[0-9] soqt[0-9] sowin[0-9]"
      for lib in $debuglibs; do
        if test x"`echo $value | sed -e "s%$lib%%"`" = x""; then
          value="${value}d"
          break
        fi
      done
      debuglibfiles="$debuglibfiles ${value}.lib"
      ;;
    -L* )
      value=`echo $arg | cut -c3-`
      if test x"$sourcedir" != x""; then
        curdir=`pwd`
        value=`echo $value | sed -e "s%$sourcedir%$curdir%"`
      fi
      # if $value is not a subdir of $source
      if ! issubdir "$sourcedir" "$value"; then
        windir=`substitute_dir $value`
        libdirs="$libdirs /libpath:\"`echo $windir | sed -e 's%\\\\%\\\\\\\\%g'`\""
      fi
      ;;
    -I* )
      value=`echo $arg | cut -c3-`
      if test x"$sourcedir" != x""; then
        curdir=`pwd`
        value=`echo $value | sed -e "s%$sourcedir%$curdir%"`
      fi
      # if $value is not a subdir of $source
      if ! issubdir "$sourcedir" "$value"; then
        windir=`substitute_dir $value`
        includedirs="$includedirs /I\"`echo $windir | sed -e 's%\\\\%\\\\\\\\%g'`\""
      fi
      ;;
    -D* )
      value=`echo $arg | cut -c3-`
      defines="$defines /D$value"
      ;;
    -* )
      ;;
    * )
      if test x"$sourcefile" = x"get"; then
        sourcefile=$arg
      elif test x"$dependfile" = x"get"; then
        dependfile=$arg
      fi
      stem=`echo $arg | sed -e 's/\..*$//g'`
      extension=`echo $arg | sed -e 's/.*\.//g'`
      if test x"$extension" = x"obj"; then
        sourcefiles="$sourcefiles $stem.cpp"
      fi
      ;;
    esac
  fi
done

if test x"$sourcefile" = x""; then :; else
  usource=`cygpath -u $sourcefile`
  justname=`echo $usource | sed -e "s%.*/%%"`
  if test -e $justname; then :; else
    cp $usource .
  fi
  if test x"$objectfile" = x""; then
    objectfile=`echo $sourcefile | sed -e 's%^.*[/\\\\]%%g' -e 's%\.\(cpp\|c\)$%.o%'`
  fi
fi

if test x"$objectfile" = x""; then :; else
  date >$objectfile
fi

if test x"$dependfile" = x""; then :; else
  echo "" >$dependfile
fi

stem=`echo $outputfile | sed -e 's/\..*$//g'`
extension=`echo $outputfile | sed -e 's/.*\.//g'`
if ! test x"$extension" = x"exe"; then
  exit
fi

echo "gendspex.sh: Creating $stem.dsp and $stem.dsw"

if test -e sourcefiles.txt; then
  rm sourcefiles.txt
fi

for filename in $sourcefiles; do
  cat $sourcedir/cfg/$project_template_source | sed -e "s%@SOURCEFILE@%$filename%g">>sourcefiles.txt
done

cat $sourcedir/cfg/$project_template_main | sed -e "s/@PROJECTNAME@/$stem/g" \
    -e "s%@DEBUG_DEFINES@%$defines $includedirs%g" \
    -e "s%@RELEASE_DEFINES@%$defines $includedirs%g" \
    -e "s%@DEBUG_LIBS@%$libdirs $debuglibfiles%g" \
    -e "s%@RELEASE_LIBS@%$libdirs $releaselibfiles%g" \
    -e "/@SOURCEFILES@/r sourcefiles.txt" \
    -e "s/@SOURCEFILES@//g" \
    > "$stem.dsp.txt"

rm "sourcefiles.txt"

cat $sourcedir/cfg/$workspace_template | sed -e "s/@PROJECTNAME@/$stem/g" > "$stem.dsw.txt"

# do unix2dos conversion (\n -> \r\n)
echo -e "s/\$/\r/;\np;" >unix2dos.sed
sed -n -f unix2dos.sed "$stem.dsp.txt" >"$stem.dsp"
sed -n -f unix2dos.sed "$stem.dsw.txt" >"$stem.dsw"
# clean out temporary files
rm -f "$stem.dsp.txt" "$stem.dsw.txt" "unix2dos.sed"



