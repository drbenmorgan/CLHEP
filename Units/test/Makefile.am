# Applicable to each test program:
INCLUDES = -I../
LDADD = @Units_LDFLAGS@  @Units_LIBS@	# libraries to link, and whence

# Identify executables needed during testing:
check_PROGRAMS = \
	testUnits

check_SCRIPTS = \
	testUnits.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
	testUnits.sh

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testUnits_SOURCES = testUnits.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
	testUnits.input	testUnits.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES =
