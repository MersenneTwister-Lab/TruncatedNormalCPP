if HAVE_DOXYGEN
#directory = $(top_srcdir)/doc/

#dist_man_MANS = $(directory)/index.html
incdir = $(top_srcdir)/include/MCQMCIntegration
incfiles = $(incdir)/DigitalNet.h \
	$(incdir)/MCQMCIntegration.h \
	$(incdir)/BotevAlgorithm.h \
	$(incdir)/TruncatedNormal.h

#../html/index.html: mainpage.txt $(incfiles) doxyfile.stamp

doxyfile.stamp: mainpage.txt $(incfiles)
	$(DOXYGEN) doxygen.cfg
	echo Timestamp > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
endif
