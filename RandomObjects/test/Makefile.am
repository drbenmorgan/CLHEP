# run gaussSpeed and gaussSmall interactively

if USE_GMAKE
  MAKE = gmake
endif
# Applicable to each test program:
INCLUDES = -I$(top_builddir)/
# libraries to link, and whence
if BUILD_STATIC
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.a \
          ${top_builddir}/../Random/src/libCLHEP-Random-@VERSION@.a \
	  ${top_builddir}/../Matrix/src/libCLHEP-Matrix-@VERSION@.a \
	  ${top_builddir}/../Vector/src/libCLHEP-Vector-@VERSION@.a
  OUTFLAG = -o $@
else
if BUILD_VISUAL
  LDADD = $(top_builddir)/src/CLHEP-@PACKAGE@-@VERSION@.$(SHEXT) \
          ${top_builddir}/../Random/src/CLHEP-Random-@VERSION@.$(SHEXT) \
	  ${top_builddir}/../Matrix/src/CLHEP-Matrix-@VERSION@.$(SHEXT) \
	  ${top_builddir}/../Vector/src/CLHEP-Vector-@VERSION@.$(SHEXT)
  OUTFLAG = /Fo$@
else
  LIBS += $(MY_LD)$(top_builddir)/src \
          $(MY_LD)${top_builddir}/../Random/src \
          $(MY_LD)${top_builddir}/../Matrix/src \
          $(MY_LD)${top_builddir}/../Vector/src
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.$(SHEXT) \
          ${top_builddir}/../Random/src/libCLHEP-Random-@VERSION@.$(SHEXT) \
	  ${top_builddir}/../Matrix/src/libCLHEP-Matrix-@VERSION@.$(SHEXT) \
	  ${top_builddir}/../Vector/src/libCLHEP-Vector-@VERSION@.$(SHEXT)
  OUTFLAG = -o $@
endif
endif

# normally, CXXLINK is supplied by automake, but we need to use /Fo instead
# of -o when compiling with Visual C++
CXXLINK = $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) \
          $(OUTFLAG)

# Identify executables needed during testing:
check_PROGRAMS = \
	testVectorDists

check_SCRIPTS = \
	testVectorDists.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
	testVectorDists.sh

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testVectorDists_SOURCES = testVectorDists.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = \
	testVectorDists.input testVectorDists.output

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = testVectorDists.sh 

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
