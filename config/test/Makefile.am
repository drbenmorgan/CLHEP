# Applicable to each test program:
INCLUDES = -I../
LDADD = @config_LDFLAGS@  @config_LIBS@	# libraries to link, and whence

# Identify executables needed during testing:
check_PROGRAMS = \
	testConfig

check_SCRIPTS = \
	testConfig.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
	testConfig.sh

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testConfig_SOURCES = testConfig.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
	testConfig.input	testConfig.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES =
