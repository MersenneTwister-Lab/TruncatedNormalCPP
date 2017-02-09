digital_header = digital.h bit_operator.h powtwo.h config.h
compute_header = compute.h gray.hpp matrix_rank.hpp powtwo.h bit_operator.h \
config.h kahan.hpp

lib_LIBRARIES = libtrmvnorm.a
noinst_PROGRAMS = sample

libtrmvnorm_a_SOURCES = TruncatedNormal.cpp \
	MCQMCIntegration.cpp \
	DigitalNet.cpp $(digital_header) \
	BotevAlgorithm.cpp \
	pnorm.cpp pnorm.h #kahan.hpp

sample_DEPENDENCIES = ./libtrmvnorm.a
sample_SOURCES = sample.cpp
sample_LDADD = -ltrmvnorm
sample_LDFLAGS = -L./

#AM_LDFLAGS = -L./
AM_CXXFLAGS = -I../include -O3 -Wall -Wextra -D__STDC_CONSTANT_MACROS
