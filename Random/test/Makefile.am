# run gaussSpeed and gaussSmall interactively
# Applicable to each test program:

if USE_GMAKE
  MAKE = gmake
endif
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
	testRandom testRandDists gaussSpeed gaussSmall \
	testSaveEngineStatus testInstanceRestore testSaveSharedEngines \
	testStaticStreamSave testAnonymousEngineRestore testVectorSave

check_SCRIPTS = \
	testRandom.sh testRandDists.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
	testRandom.sh testRandDists.sh \
	testSaveEngineStatus testInstanceRestore testSaveSharedEngines \
	testStaticStreamSave testAnonymousEngineRestore testVectorSave

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testRandDists_SOURCES = testRandDists.cc
testRandom_SOURCES = testRandom.cc
testSaveEngineStatus_SOURCES = testSaveEngineStatus.cc
testInstanceRestore_SOURCES = testInstanceRestore.cc
testSaveSharedEngines_SOURCES = testSaveSharedEngines.cc
testStaticStreamSave_SOURCES = testStaticStreamSave.cc
testAnonymousEngineRestore_SOURCES = testAnonymousEngineRestore.cc
testVectorSave_SOURCES = testVectorSave.cc
gaussSpeed_SOURCES = gaussSpeed.cc
gaussSmall_SOURCES = gaussSmall.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
	testRandom.input testRandDists.input testRandDists.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = testRandom.sh testRandDists.sh  \
	gaussSpeed.sh gaussSmall.sh testRandom.out \
	distribution.save distribution.save1 distribution.save2 \
	engine.save shared.save1 shared.save2 \
	testSaveEngineStatus.cout testInstanceRestore.cout \
	testSaveSharedEngines.cout testStaticStreamSave.cout \
	testAnonymousEngineRestore.cout testVectorSave.cout \
	anonymous.save
