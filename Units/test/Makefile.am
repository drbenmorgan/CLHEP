# Applicable to each test program:

if USE_GMAKE
  MAKE = gmake
endif
INCLUDES = -I../
LDADD = @Units_LDFLAGS@  @Units_LIBS@	# libraries to link, and whence

if BUILD_VISUAL
  OUTFLAG = /Fo$@
else
  OUTFLAG = -o $@
endif

# normally, CXXLINK is supplied by automake, but we need to use /Fo instead
# of -o when compiling with Visual C++
CXXLINK = $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) \
          $(OUTFLAG)

# Identify executables needed during testing:
check_PROGRAMS = \
	testUnits

check_SCRIPTS = 

# Identify test(s) to run when 'make check' is requested:
TESTS = \
	testUnits

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = 

# Identify the dependencies on a per-test basis:
testUnits_SOURCES = testUnits.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST = 

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES =

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
