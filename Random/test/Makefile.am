# Applicable to each test program:
INCLUDES = -I../
LDADD = -L${top_builddir}/src  @Random_LIBS@	# libraries to link, and whence

# Identify executables needed during testing:
check_PROGRAMS = \
	testRandDists

check_SCRIPTS = \
	testRandDists.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
	testRandDists.sh

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testRandDists_SOURCES = testRandDists.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
	testRandDists.input	testRandDists.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES =
