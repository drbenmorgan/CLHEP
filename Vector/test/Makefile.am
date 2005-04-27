# Applicable to each test program:

if USE_GMAKE
  MAKE = gmake
endif

INCLUDES = -I$(top_builddir)/

# libraries to link, and whence
if BUILD_STATIC
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.a
else
  LIBS += $(MY_LD)$(top_builddir)/src
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.$(SHEXT)
endif

# Identify executables needed during testing:
check_PROGRAMS = \
	testThreeVector testLorentzVector testRotation testSubscripts

check_SCRIPTS = \
	testThreeVector.sh testLorentzVector.sh testRotation.sh testSubscripts.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
	testThreeVector.sh testLorentzVector.sh testRotation.sh testSubscripts.sh


# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testThreeVector_SOURCES = testThreeVector.cc
testLorentzVector_SOURCES = testLorentzVector.cc
testRotation_SOURCES = testRotation.cc
testSubscripts_SOURCES = testSubscripts.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
	testThreeVector.input	testThreeVector.output \
	testLorentzVector.input testLorentzVector.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = testThreeVector.sh testLorentzVector.sh testRotation.sh testSubscripts.sh
