# Applicable to each test program:
INCLUDES = -I../
# libraries to link, and whence
LDADD = $(top_builddir)/src/.libs/libCLHEP-@PACKAGE@-@VERSION@.lib        \
        ${top_builddir}/../Geometry/src/.libs/libCLHEP-Geometry-@VERSION@.lib \
	${top_builddir}/../Vector/src/.libs/libCLHEP-Vector-@VERSION@.lib     \
	${top_builddir}/../GenericFunctions/src/.libs/libCLHEP-GenericFunctions-@VERSION@.lib

# Identify executables needed during testing:
check_PROGRAMS = \
	testXF

check_SCRIPTS = \
	testXF.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
	testXF.sh

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testXF_SOURCES = testXF.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
	testXF.input	testXF.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES =
