# Applicable to each test program:

if USE_GMAKE
  MAKE = gmake
endif
INCLUDES = -I../
LDADD = @Utility_LDFLAGS@  @Utility_LIBS@	# libraries to link, and whence

if BUILD_VISUAL
  OUTFLAG = /Fo$@
else
  CXXFLAGS +=  -Wno-non-virtual-dtor
  OUTFLAG = -o $@
endif

# normally, CXXLINK is supplied by automake, but we need to use /Fo instead
# of -o when compiling with Visual C++
CXXLINK = $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) $(AM_LDFLAGS) $(LDFLAGS) \
          $(OUTFLAG)

# Identify executables needed during testing:
check_PROGRAMS =	\
	testNoncopyable	\
	testPrimaryTraits	\
	testCategories	\
	testIsSame	\
	testIsConvertible	\
	testSharedPtrBasic	\
	testSharedPtrConvertible	\
	testSharedPtr	\
	testWeakPtr	

# Identify test(s) to run when 'make check' is requested:
TESTS =	\
	testNoncopyable	\
	testPrimaryTraits	\
	testCategories	\
	testIsSame	\
	testIsConvertible	\
	testSharedPtrBasic	\
	testSharedPtrConvertible	\
	testSharedPtr	\
	testWeakPtr	

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS =

# Identify the dependencies on a per-test basis:
testNoncopyable_SOURCES = testNoncopyable.cc
testPrimaryTraits_SOURCES = testPrimaryTraits.cc
testCategories_SOURCES = testCategories.cc
testIsSame_SOURCES = testIsSame.cc
testIsConvertible_SOURCES = testIsConvertible.cc
testSharedPtrBasic_SOURCES = testSharedPtrBasic.cc
testSharedPtrConvertible_SOURCES = testSharedPtrConvertible.cc
testSharedPtr_SOURCES = testSharedPtr.cc
testWeakPtr_SOURCES = testWeakPtr.cc

# Identify input data file(s) and prototype output file(s):
EXTRA_DIST =

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES =

# supply our own suffix rule
.cc.obj:
if BUILD_VISUAL
	source='$<' object='$@' libtool=no \
	DEPDIR=$(DEPDIR) $(CXXDEPMODE) $(depcomp) \
	$(CXXCOMPILE) -c $(OUTFLAG) `$(CYGPATH_W) '$<'`
else
	if $(CXXCOMPILE) -MT $@ -MD -MP -MF "$(DEPDIR)/$*.Tpo" -c $(OUTFLAG) `$(CYGPATH_W) '$<'`; \
	then mv -f "$(DEPDIR)/$*.Tpo" "$(DEPDIR)/$*.Po"; else rm -f "$(DEPDIR)/$*.Tpo"; exit 1; fi
endif
