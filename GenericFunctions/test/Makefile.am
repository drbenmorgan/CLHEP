# Applicable to each test program:
INCLUDES = -I../
LDADD =  $(top_builddir)/src/.libs/libCLHEP-@PACKAGE@-@VERSION@.lib	# libraries to link, and whence

# Identify executables needed during testing:
check_PROGRAMS = \
	testGenericFunctions

check_SCRIPTS = \
	testGenericFunctions.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
	testGenericFunctions.sh

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testGenericFunctions_SOURCES = testGenericFunctions.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
	testGenericFunctions.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES =
