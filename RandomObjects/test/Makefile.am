# run gaussSpeed and gaussSmall interactively
# Applicable to each test program:
INCLUDES = -I../
# libraries to link, and whence
LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.la \
        ${top_builddir}/../Random/src/libCLHEP-Random-@VERSION@.la \
	${top_builddir}/../Matrix/src/libCLHEP-Matrix-@VERSION@.la

# Identify executables needed during testing:
check_PROGRAMS = \
	testVectorDists

check_SCRIPTS = \
	testVectorDists.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
	testVectorDists.sh

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testVectorDists_SOURCES = testVectorDists.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
	testVectorDists.input testVectorDists.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = testVectorDists.sh 
