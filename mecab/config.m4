dnl
dnl $ Id: $
dnl

PHP_ARG_WITH(mecab, [whether to enable MeCab support],
[  --with-mecab[[=PATH]]     Enable MeCab support.
                          PATH is the optional pathname to mecab-config], yes, yes)

if test "$PHP_MECAB" != "no"; then

  if test -z "$AWK"; then
    AC_PATH_PROGS(AWK, awk gawk nawk, [no])
  fi
  if test -z "$SED"; then
    AC_PATH_PROGS(SED, sed gsed, [no])
  fi

  dnl
  dnl Check the location of mecab-config
  dnl
  if test "$PHP_MECAB" != "yes"; then
    AC_MSG_CHECKING([for mecab-config])
    if test -f "$PHP_MECAB"; then
      MECAB_CONFIG="$PHP_MECAB"
    elif test -f "$PHP_MECAB/mecab-config"; then
      MECAB_CONFIG="$PHP_MECAB/mecab-config"
    elif test -f "$PHP_MECAB/bin/mecab-config"; then
      MECAB_CONFIG="$PHP_MECAB/bin/mecab-config"
    else
      AC_MSG_ERROR([not found])
    fi
    AC_MSG_RESULT([$MECAB_CONFIG])
  else
    AC_PATH_PROGS(MECAB_CONFIG, mecab-config, [])
    if test -z "$MECAB_CONFIG"; then
      AC_MSG_ERROR([mecab-config not found])
    fi
  fi

  dnl
  dnl Get the version number, CFLAGS and LIBS by mecab-config
  dnl
  AC_MSG_CHECKING([for MeCab library version])

  MECAB_VERSION_STRING=`$MECAB_CONFIG --version 2> /dev/null`
  MECAB_CFLAGS=`$MECAB_CONFIG --cflags 2> /dev/null`
  MECAB_LIBS=`$MECAB_CONFIG --libs 2> /dev/null`

  if test -z "$MECAB_VERSION_STRING"; then
    AC_MSG_ERROR([invalid mecab-config passed to --with-mecab])
  fi

  MECAB_VERSION_NUMBER=`echo $MECAB_VERSION_STRING | $AWK -F. '{ printf "%d", $1 * 1000 + $2 }'`

  if test "$MECAB_VERSION_NUMBER" -ne 99 -a "$MECAB_VERSION_NUMBER" -lt 99; then
    AC_MSG_RESULT([$MECAB_VERSION_STRING])
    AC_MSG_ERROR([MeCab version 0.99 or later is required to compile php with MeCab support])
  fi

  AC_DEFINE_UNQUOTED(PHP_MECAB_VERSION_NUMBER, $MECAB_VERSION_NUMBER, [MeCab library version number])
  AC_DEFINE_UNQUOTED(PHP_MECAB_VERSION_STRING, "$MECAB_VERSION_STRING", [MeCab library version string])
  AC_MSG_RESULT([$MECAB_VERSION_STRING (ok)])

  dnl
  dnl Check the headers and types
  dnl
  export OLD_CPPFLAGS="$CPPFLAGS"
  export CPPFLAGS="$CPPFLAGS $MECAB_CFLAGS"
  AC_CHECK_HEADER([mecab.h], [], AC_MSG_ERROR([mecab.h header not found]))
  export CPPFLAGS="$OLD_CPPFLAGS"

  dnl
  dnl Check the library
  dnl
  export OLD_LIBS="$LIBS"
  export LIBS="$OLD_LIBS -lpthread"
  PHP_CHECK_LIBRARY(mecab, mecab_new2,
    [
      PHP_EVAL_INCLINE($MECAB_CFLAGS)
      PHP_EVAL_LIBLINE($MECAB_LIBS, MECAB_SHARED_LIBADD)
    ],[
      AC_MSG_ERROR([wrong MeCab library version or lib not found. Check config.log for more information])
    ],[
      $MECAB_LIBS
    ])
  export LIBS="$OLD_LIBS"

  PHP_SUBST(MECAB_SHARED_LIBADD)
  PHP_MECAB_PHP_VERSION=`$PHP_CONFIG --version 2>/dev/null`
  PHP_MECAB_PHP_VERNUM=`$PHP_CONFIG --vernum 2>/dev/null`
  AC_MSG_CHECKING([for PHP version])
  AC_MSG_RESULT([build for $PHP_MECAB_PHP_VERSION])
  if test "$PHP_MECAB_PHP_VERNUM" -ge 70000; then
    PHP_NEW_EXTENSION(mecab, mecab7.c , $ext_shared)
  else
    PHP_NEW_EXTENSION(mecab, mecab5.c , $ext_shared)
  fi
fi
