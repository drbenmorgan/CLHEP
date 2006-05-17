# Applicable to each test program:

if USE_GMAKE
  MAKE = gmake
endif
INCLUDES = -I$(top_builddir)/

# libraries to link, and whence
if BUILD_STATIC
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.a \
          $(top_builddir)/../Vector/src/libCLHEP-Vector-@VERSION@.a
else
if BUILD_VISUAL
  LDADD = $(top_builddir)/src/CLHEP-@PACKAGE@-@VERSION@.$(SHEXT) \
          $(top_builddir)/../Vector/src/CLHEP-Vector-@VERSION@.$(SHEXT)
else
  LIBS += $(MY_LD)$(top_builddir)/src \
	  $(MY_LD)$(top_builddir)/../Vector/src
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.$(SHEXT) \
          $(top_builddir)/../Vector/src/libCLHEP-Vector-@VERSION@.$(SHEXT)
endif
endif

# Identify executables needed during testing:
check_PROGRAMS = \
        testDoubleConversion testRandomState testPrintBug

check_SCRIPTS = testPrintBug.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
        testDoubleConversion testRandomState testPrintBug.sh

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testDoubleConversion_SOURCES = testDoubleConversion.cc
testRandomState_SOURCES      = testRandomState.cc
testPrintBug_SOURCES         = testPrintBug.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = testPrintBug.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES =
