# Applicable to each test program:
INCLUDES = -I../
LDADD = -L${top_builddir}/src  @HepPDT_LIBS@    # libraries to link, and whence

# Identify executables needed during testing:
check_PROGRAMS = \
        testPID testHepPDT

check_SCRIPTS = \
        testPID.sh testHepPDT.sh testHepPDT.input

# Identify test(s) to run when 'make check' is requested:
TESTS = \
        testPID.sh testHepPDT.sh

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testPID_SOURCES = testPID.cc

testHepPDT_SOURCES = testHepPDT.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
        testPID.output testHepPDT.output testHepPDT.input

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES =
