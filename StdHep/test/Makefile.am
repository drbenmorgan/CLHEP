# Applicable to each test program:
INCLUDES = -I$(top_builddir)/

# libraries to link, and whence
if BUILD_STATIC
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.a \
          $(top_builddir)/../HepMC/src/libCLHEP-HepMC-@VERSION@.a \
          $(top_builddir)/../Random/src/libCLHEP-Random-@VERSION@.a
else
  LIBS += $(MY_LD)$(top_builddir)/src
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.$(SHEXT) \
          $(top_builddir)/../HepMC/src/libCLHEP-HepMC-@VERSION@.$(SHEXT) \
          $(top_builddir)/../Random/src/libCLHEP-Random-@VERSION@.$(SHEXT)
endif

# Identify executables needed during testing:
check_PROGRAMS = \
        testStdRandom

#check_SCRIPTS =

# Identify test(s) to run when 'make check' is requested:
TESTS = \
        testStdRandom

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testStdRandom_SOURCES      = testStdRandom.cc SimpleRand.cc

# Identify input data file(s) and prototype output file(s):
#EXTRA_DIST = 

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES =
