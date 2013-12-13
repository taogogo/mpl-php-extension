dnl $Id$
dnl config.m4 for extension mpl

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(mpl, for mpl support,
Make sure that the comment is aligned:
[  --with-mpl             Include mpl support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(mpl, whether to enable mpl support,
dnl Make sure that the comment is aligned:
dnl [  --enable-mpl           Enable mpl support])

if test "$PHP_MPL" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-mpl -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/mpl.h"  # you most likely want to change this
  dnl if test -r $PHP_MPL/$SEARCH_FOR; then # path given as parameter
  dnl   MPL_DIR=$PHP_MPL
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for mpl files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       MPL_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$MPL_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the mpl distribution])
  dnl fi

  dnl # --with-mpl -> add include path
  dnl PHP_ADD_INCLUDE($MPL_DIR/include)

  dnl # --with-mpl -> check for lib and symbol presence
  dnl LIBNAME=mpl # you may want to change this
  dnl LIBSYMBOL=mpl # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MPL_DIR/lib, MPL_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_MPLLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong mpl lib version or lib not found])
  dnl ],[
  dnl   -L$MPL_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(MPL_SHARED_LIBADD)

  PHP_NEW_EXTENSION(mpl, mpl.c, $ext_shared)
fi
