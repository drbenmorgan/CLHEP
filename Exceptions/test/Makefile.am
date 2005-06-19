# Applicable to each test program:

if USE_GMAKE
  MAKE = gmake
endif
INCLUDES = -I$(top_builddir)/

# libraries to link, and whence
if BUILD_STATIC
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.a    \
	  ${top_builddir}/../Cast/src/libCLHEP-Cast-@VERSION@.a \
	  ${top_builddir}/../RefCount/src/libCLHEP-RefCount-@VERSION@.a
else
if BUILD_VISUAL
else
  LIBS += $(MY_LD)$(top_builddir)/src \
          $(MY_LD)${top_builddir}/../Cast/src \
          $(MY_LD)${top_builddir}/../RefCount/src
endif
  LDADD = $(top_builddir)/src/libCLHEP-@PACKAGE@-@VERSION@.$(SHEXT)    \
	  ${top_builddir}/../Cast/src/libCLHEP-Cast-@VERSION@.$(SHEXT) \
	  ${top_builddir}/../RefCount/src/libCLHEP-RefCount-@VERSION@.$(SHEXT)
endif

# Identify executables needed during testing:
check_PROGRAMS = \
	testExceptions 	\
	testzmex	\
	testThrowFrom	\
	exctest1 	\
	exctest2 	\
	exctest3 	\
	exctest4 	\
 	exctestNothrow	\
 	excDblThrow

check_SCRIPTS = \
	testExceptions.sh 	\
	testzmex.sh		\
	testThrowFrom.sh	\
	exctest1.sh 		\
	exctest2.sh 		\
	exctest3.sh 		\
	exctest4.sh 		\
 	exctestNothrow.sh	\
 	excDblThrow.sh

# Identify test(s) to run when 'make check' is requested:
TESTS = \
	testExceptions.sh 	\
	testzmex.sh		\
	testThrowFrom.sh	\
	exctest1.sh 		\
	exctest2.sh 		\
	exctest3.sh 		\
	exctest4.sh 		\
 	exctestNothrow.sh	

# 	excDblThrow.sh

# Identify the test(s) for which failure is the intended outcome:
XFAIL_TESTS = testzmex.sh

# Identify the dependencies on a per-test basis:
testExceptions_SOURCES = testExceptions.cc
testzmex_SOURCES = testzmex.cc
testThrowFrom_SOURCES = testThrowFrom.cc
exctest1_SOURCES = exctest1.cc
exctest2_SOURCES = exctest2.cc
exctest3_SOURCES = exctest3.cc
exctest4_SOURCES = exctest4.cc
exctestNothrow_SOURCES = exctestNothrow.cc	
excDblThrow_SOURCES = excDblThrow.cc

# Identify input data file(s) and prototype output file(s):
#EXTRA_DIST = testExceptions.input testExceptions.output 

# Identify generated file(s) to be removed when 'make clean' is requested:
CLEANFILES = \
	testExceptions.sh 	\
	testzmex.sh		\
	testThrowFrom.sh	\
	exctest1.sh 		\
	exctest2.sh 		\
	exctest3.sh 		\
	exctest4.sh 		\
 	exctestNothrow.sh     	\
 	excDblThrow.sh

