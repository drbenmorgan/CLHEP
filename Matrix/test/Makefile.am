# Applicable to each test program:

if USE_GMAKE
  MAKE = gmake
endif
INCLUDES = -I$(top_builddir)/

# libraries to link, and whence
if BUILD_STATIC
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.a \
          ${top_builddir}/../Random/src/libCLHEP-Random-@VERSION@.a \
	  ${top_builddir}/../Vector/src/libCLHEP-Vector-@VERSION@.a
else
  LIBS += $(MY_LD)$(top_builddir)/src \
          $(MY_LD)${top_builddir}/../Random/src \
          $(MY_LD)${top_builddir}/../Vector/src
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.$(SHEXT) \
          ${top_builddir}/../Random/src/libCLHEP-Random-@VERSION@.$(SHEXT) \
	  ${top_builddir}/../Vector/src/libCLHEP-Vector-@VERSION@.$(SHEXT)
endif

# add -D needed by testInversion
CXXFLAGS = @CXXFLAGS@ -DINSTALLATION_CHECK

# Identify executables needed during testing:
check_PROGRAMS = \
	testMatrix testInversion \
	testBug6176 testBug6181 testBug7328

check_SCRIPTS = \
	testMatrix.sh testInversion.sh \
	testBug6176.sh 

# Identify test(s) to run when 'make check' is requested:
TESTS = \
	testMatrix.sh testInversion.sh \
	testBug6176.sh testBug6181 testBug7328

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testMatrix_SOURCES = testMatrix.cc
testInversion_SOURCES = testInversion.cc
testBug6176_SOURCES = testBug6176.cc
testBug6181_SOURCES = testBug6181.cc
testBug7328_SOURCES = testBug7328.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
	testMatrix.output testInversion.output \
	testBug6176.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = testMatrix.sh testInversion.sh \
	testBug6176.sh

