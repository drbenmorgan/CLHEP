# Applicable to each test program:
INCLUDES = -I../
# libraries to link, and whence
LDADD = ${top_builddir}/src/libCLHEP-@PACKAGE@-@VERSION@.la \
        ${top_builddir}/../Random/src/libCLHEP-Random-@VERSION@.la \
	${top_builddir}/../Vector/src/libCLHEP-Vector-@VERSION@.la
# add -D needed by testInversion
CXXFLAGS = @CXXFLAGS@ -DINSTALLATION_CHECK

# Identify executables needed during testing:
check_PROGRAMS = \
	testMatrix testInversion

check_SCRIPTS = \
	testMatrix.sh testInversion.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
	testMatrix.sh testInversion.sh

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testMatrix_SOURCES = testMatrix.cc
testInversion_SOURCES = testInversion.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
	testMatrix.output testInversion.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = testMatrix.sh testInversion.sh
