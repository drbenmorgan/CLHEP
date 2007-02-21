# Applicable to each test program:

if USE_GMAKE
  MAKE = gmake
endif
INCLUDES = -I$(top_builddir)/

# libraries to link, and whence
if BUILD_STATIC
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.a
else
if BUILD_VISUAL
  LDADD = $(top_builddir)/src/CLHEP-@PACKAGE@-@VERSION@.$(SHEXT)
else
  LIBS += $(MY_LD)$(top_builddir)/src
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.$(SHEXT)
endif
endif

# Identify executables needed during testing:
check_PROGRAMS = \
        testPID testHepPDT listQQTranslation listParticleNames \
	listPythiaNames listPDGNames readIsajet

check_SCRIPTS = \
        testPID.sh testHepPDT.sh testHepPDT.input \
	listQQTranslation.sh listParticleNames.sh listPythiaNames.sh \
	listPDGNames.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
        testPID.sh testHepPDT.sh listQQTranslation.sh listParticleNames.sh \
	listPythiaNames.sh listPDGNames.sh readIsajet

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testPID_SOURCES = testPID.cc

testHepPDT_SOURCES = testHepPDT.cc

readIsajet_SOURCES = readIsajet.cc

listQQTranslation_SOURCES = listQQTranslation.cc

listParticleNames_SOURCES = listParticleNames.cc

listPythiaNames_SOURCES = listPythiaNames.cc

listPDGNames_SOURCES = listPDGNames.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
        testPID.output testHepPDT.output testHepPDT.input \
	listQQ.dec listQQTranslation.output listParticleNames.output \
	listPythia.tbl listPythiaNames.output listPDGNames.output 

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES =
