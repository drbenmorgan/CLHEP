# run gaussSpeed and gaussSmall interactively
# Applicable to each test program:
INCLUDES = -I$(top_builddir)

# libraries to link, and whence
if BUILD_STATIC
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.a
else
  LIBS += $(MY_LD)$(top_builddir)/src
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.$(SHEXT)
endif

# Identify executables needed during testing:
check_PROGRAMS = \
	testRandom testRandDists ranRestoreTest gaussSpeed gaussSmall

check_SCRIPTS = \
	testRandom.sh testRandDists.sh ranRestoreTest.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
	testRandom.sh testRandDists.sh ranRestoreTest.sh

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testRandDists_SOURCES = testRandDists.cc
testRandom_SOURCES = testRandom.cc
ranRestoreTest_SOURCES = ranRestoreTest.cc
gaussSpeed_SOURCES = gaussSpeed.cc
gaussSmall_SOURCES = gaussSmall.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
	testRandom.input testRandDists.input testRandDists.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = testRandom.sh testRandDists.sh ranRestoreTest.sh \
	gaussSpeed.sh gaussSmall.sh testRandom.out ranRestoreTest.out
