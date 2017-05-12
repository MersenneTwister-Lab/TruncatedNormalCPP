#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([TruncatedNormalCPP], [0.2.2], [saito@manieth.com])
#LT_INIT
AC_CONFIG_SRCDIR([src/Makefile.am])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE
LT_INIT
AC_PROG_RANLIB
AC_CANONICAL_HOST

# Checks for programs.
: ${CFLAGS=""}
: ${CXXFLAGS=""}
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL

# Checks for header files.
#AC_HEADER_STDC
#AX_EXT


AC_LANG_PUSH(C++)
#AX_CXX_COMPILE_STDCXX_0X

AX_CXX_COMPILE_STDCXX_14(noext, optional) // keep this order
AX_CXX_COMPILE_STDCXX_11(noext, mandatory)

AC_CHECK_HEADERS([inttypes.h stdint.h stdlib.h])

AX_BOOST_BASE([1.48],,
[AC_MSG_ERROR([libbotev needs Boost, but it was not found in your system])])

AC_CHECK_HEADER(boost/numeric/ublas/vector.hpp, [], \
[libbotev needs Boost UBLAS vector.hpp, but it was not found in your system])
AC_CHECK_HEADER(boost/numeric/ublas/matrix.hpp, [], \
[libbotev needs Boost UBLAS matrix.hpp, but it was not found in your system])
AC_CHECK_HEADER(boost/numeric/ublas/io.hpp, [], \
[libbotev needs Boost UBLAS io.hpp, but it was not found in your system])
AC_CHECK_HEADER(boost/numeric/ublas/lu.hpp, [], \
[libbotev needs Boost UBLAS lu.hpp, but it was not found in your system])
AC_CHECK_HEADER(boost/numeric/ublas/triangular.hpp, [], \
[libbotev needs Boost UBLAS triangular.hpp, \
but it was not found in your system])

AC_LANG_POP

AX_GCC_BUILTIN(__builtin_popcount)
AX_GCC_BUILTIN(__builtin_popcountl)
AX_GCC_BUILTIN(__builtin_popcountll)

AC_CHECK_PROGS([DOXYGEN], [doxygen])
if test -z "$DOXYGEN";
   then AC_MSG_WARN([Doxygen not found - continuing without Doxygen support])
fi
AM_CONDITIONAL([HAVE_DOXYGEN], [test -n "$DOXYGEN"])

AC_CONFIG_FILES([Makefile \
src/Makefile \
include/Makefile \
example/Makefile \
doxygen/Makefile])
AC_OUTPUT
