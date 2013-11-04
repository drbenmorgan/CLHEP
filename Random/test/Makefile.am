# run gaussSpeed and gaussSmall interactively
# Applicable to each test program:

if USE_GMAKE
  MAKE = gmake
endif
INCLUDES = -I$(top_builddir)

# libraries to link, and whence
if BUILD_STATIC
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.a
  OUTFLAG = -o $@
else
if BUILD_VISUAL
  LDADD = $(top_builddir)/src/CLHEP-@PACKAGE@-@VERSION@.$(SHEXT)
  OUTFLAG = /Fo$@
else
  LIBS += $(MY_LD)$(top_builddir)/src
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.$(SHEXT)
  OUTFLAG = -o $@
endif
endif

# normally, CXXLINK is supplied by automake, but we need to use /Fo instead
# of -o when compiling with Visual C++
CXXLINK = $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) \
          $(OUTFLAG)

# Identify executables needed during testing:
check_PROGRAMS = \
	testRandom testRandDists gaussSpeed gaussSmall \
	testSaveEngineStatus testInstanceRestore testSaveSharedEngines \
	testStaticStreamSave testAnonymousEngineRestore testVectorSave \
	testBug58950 testBug73093 testEngineCopy testDistCopy testRanecuSequence

check_SCRIPTS = \
	testRandom.sh testRandDists.sh

# Identify test(s) to run when 'make check' is requested:
# Note that testBug58950 uses a feature not available in cygwin
if BUILD_VISUAL
TESTS = \
	testRandom.sh testRandDists.sh \
	testSaveEngineStatus testInstanceRestore testSaveSharedEngines \
	testStaticStreamSave testAnonymousEngineRestore testVectorSave \
	testBug73093 testEngineCopy testDistCopy
else
TESTS = \
	testRandom.sh testRandDists.sh \
	testSaveEngineStatus testInstanceRestore testSaveSharedEngines \
	testStaticStreamSave testAnonymousEngineRestore testVectorSave \
	testBug58950 testBug73093 testEngineCopy testDistCopy testRanecuSequence
endif

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
testEngineCopy_SOURCES = testEngineCopy.cc
testDistCopy_SOURCES = testDistCopy.cc
testRanecuSequence_SOURCES = testRanecuSequence.cc
testBug58950_SOURCES = testBug58950.cc
testBug73093_SOURCES = testBug73093.cc
gaussSpeed_SOURCES = gaussSpeed.cc
gaussSmall_SOURCES = gaussSmall.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
	testRandom.input testRandDists.input testRandDists.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = testRandom.sh testRandDists.sh  \
	gaussSpeed.sh gaussSmall.sh testRandom.out \
	distribution.save distribution.save1 distribution.save2 \
	anon_distribution.save instance_distribution.save instance2_distribution.save \
	ss1_distribution.save ss2_distribution.save ss_distribution.save \
	engine.save anon_engine.save instance_engine.save \
	shared.save1 shared.save2 t1_shared.save t2_shared.save \
	testSaveEngineStatus.cout testInstanceRestore.cout \
	testSaveSharedEngines.cout testStaticStreamSave.cout \
	testAnonymousEngineRestore.cout testVectorSave.cout \
	anonymous.save testRanecuSequence.output

# supply our own suffix rule
.cc.obj:
if BUILD_VISUAL
#	$(CXXCOMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c $(OUTFLAG) `$(CYGPATH_W) '$<'`
#	mv -f $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
	source='$<' object='$@' libtool=no \
	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
	$(CXXCOMPILE) -c $(OUTFLAG) `$(CYGPATH_W) '$<'`
else
	if $(CXXCOMPILE) -MT $@ -MD -MP -MF "$(DEPDIR)/$*.Tpo" -c $(OUTFLAG) `$(CYGPATH_W) '$<'`; \
	then mv -f "$(DEPDIR)/$*.Tpo" "$(DEPDIR)/$*.Po"; else rm -f "$(DEPDIR)/$*.Tpo"; exit 1; fi
#	source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
#	$(CXXCOMPILE) -c -o $@ `$(CYGPATH_W) '$<'`
endif
