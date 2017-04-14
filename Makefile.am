if HAVE_DOXYGEN
doc_dir = doxygen
endif
SUBDIRS = src include example $(doc_dir)

dist_pkgdata_DATA = data/*
EXTRA_DIST = docs docs/ja/*.html

ACLOCAL_AMFLAGS = -I m4
AM_CXXFLAGS = -O3 -Wall -Wextra -D__STDC_CONSTANT_MACROS
