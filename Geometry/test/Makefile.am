# Applicable to each test program:
INCLUDES = -I../
# libraries to link, and whence
LDADD = ${top_builddir}/src/libCLHEP-@PACKAGE@-@VERSION@.la \
        ${top_builddir}/../Vector/src/libCLHEP-Vector-@VERSION@.la

# Identify executables needed during testing:
check_PROGRAMS = \
	testBasicVector3D

check_SCRIPTS = \
	testBasicVector3D.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
	testBasicVector3D.sh

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testBasicVector3D_SOURCES = testBasicVector3D.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
	testBasicVector3D.input	testBasicVector3D.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES =
