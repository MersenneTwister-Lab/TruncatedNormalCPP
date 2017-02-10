noinst_PROGRAMS = qmc_example mc_example

qmc_example_DEPENDENCIES = ../src/libtrmvnorm.a
qmc_example_SOURCES = qmc_example.cpp
qmc_example_LDADD = -ltrmvnorm
qmc_example_LDFLAGS = -L../src

mc_example_DEPENDENCIES = ../src/libtrmvnorm.a
mc_example_SOURCES = mc_example.cpp
mc_example_LDADD = -ltrmvnorm
mc_example_LDFLAGS = -L../src

AM_CXXFLAGS = -I../include -O3 -Wall -Wextra -D__STDC_CONSTANT_MACROS
