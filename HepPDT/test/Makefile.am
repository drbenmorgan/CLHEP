# Applicable to each test program:
INCLUDES = -I../
LDADD = -L${top_builddir}/src  @HepPDT_LIBS@    # libraries to link, and whence

# Identify executables needed during testing:
check_PROGRAMS = \
        testPID

check_SCRIPTS = \
        testPID.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
        testPID.sh

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testPID_SOURCES = testPID.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
        testPID.input   testPID.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES =
