# Applicable to each test program:
INCLUDES = -I../
# libraries to link, and whence
LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.la

# Identify executables needed during testing:
check_PROGRAMS = \
	testEvaluator

check_SCRIPTS = \
	testEvaluator.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
	testEvaluator.sh

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testEvaluator_SOURCES = testEvaluator.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
	testEvaluator.input	testEvaluator.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES =
