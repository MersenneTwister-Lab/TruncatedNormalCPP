if HAVE_DOXYGEN
#directory = $(top_srcdir)/doc/

#dist_man_MANS = $(directory)/index.html

index.html: mainpage.txt doxyfile.stamp

doxyfile.stamp:
	$(DOXYGEN) doxygen.cfg
	echo Timestamp > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
endif
