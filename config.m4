dnl $Id$
dnl config.m4 for extension peanut

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(peanut, for peanut support,
dnl Make sure that the comment is aligned:
dnl [  --with-peanut             Include peanut support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(peanut, whether to enable peanut support,
Make sure that the comment is aligned:
[  --enable-peanut           Enable peanut support])

if test "$PHP_PEANUT" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-peanut -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/peanut.h"  # you most likely want to change this
  dnl if test -r $PHP_PEANUT/$SEARCH_FOR; then # path given as parameter
  dnl   PEANUT_DIR=$PHP_PEANUT
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for peanut files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PEANUT_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PEANUT_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the peanut distribution])
  dnl fi

  dnl # --with-peanut -> add include path
  dnl PHP_ADD_INCLUDE($PEANUT_DIR/include)

  dnl # --with-peanut -> check for lib and symbol presence
  dnl LIBNAME=peanut # you may want to change this
  dnl LIBSYMBOL=peanut # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PEANUT_DIR/lib, PEANUT_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PEANUTLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong peanut lib version or lib not found])
  dnl ],[
  dnl   -L$PEANUT_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PEANUT_SHARED_LIBADD)

  PHP_NEW_EXTENSION(peanut, peanut.c, $ext_shared)
fi
