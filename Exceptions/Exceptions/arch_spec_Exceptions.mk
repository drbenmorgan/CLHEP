# ======================================================================
#
# arch_spec_Exceptions.mk - Architecture/site-specific makefile fragment
#   for inclusion by packages that use Zoom's Exceptions package.
#
# History:
#   08-Feb-2000  WEB  Extracted from ZMutility/zoom.symbols.mk; updated
#     logic reflecting KAI 3.3+ defaults; moved into Exceptions package
#     (could later be moved into SoftRelTools package, if suffient use)
#   30-May-2002  WEB  Updated logic for post-egcs versions of gcc
#
# ======================================================================


# ----------------------------------------------------------------------
# Prepare for SRT package specialization logic:
# ----------------------------------------------------------------------

extpkg := Exceptions


# ----------------------------------------------------------------------
# Note whether exception-handling is disabled:
# ----------------------------------------------------------------------

Exceptions_USED := yes  # assume exceptions are enabled

ifeq ($(CXX),KCC)       # KCC 3.3 onward defaults to "--exceptions"
  ifeq ($(filter --no_exceptions,$(CXXFLAGS)),--no_exceptions)
    Exceptions_USED := no
  endif
endif                   # KCC

#ifeq ($(CXX),g++)       # egcs required "-fhandle-exceptions" and "-frtti"
#  ifeq ($(filter -fhandle-exceptions,$(CXXFLAGS)),)
#    Exceptions_USED := no
#  endif
#  ifeq ($(filter -frtti,$(CXXFLAGS)),)
#    Exceptions_USED := no
#  endif
#endif                   # g++

ifeq ($(CXX),g++)       # gcc 2.95.2 onward defaults to "-fexceptions"
  ifeq ($(filter -fno_exceptions,$(CXXFLAGS)),-fno_exceptions)
    Exceptions_USED := no
  endif
endif                   # g++


# ----------------------------------------------------------------------
# Connect to SRT package specialization logic:
# ----------------------------------------------------------------------

include SoftRelTools/specialize_arch_spec.mk
include SoftRelTools/arch_spec_clhep.mk

# ----------------------------------------------------------------------
# Define DEFECT_NO_EXCEPTIONS if exceptions are not used
# (in order to force an abort() call instead of a throw
# in packages that employ Zoom's Exceptions package):
# ----------------------------------------------------------------------

ifeq ($(Exceptions_USED),no)
  # avoid duplicate:
  ifneq ($(filter -DDEFECT_NO_EXCEPTIONS,$(CPPFLAGS)),-DDEFECT_NO_EXCEPTIONS)
    override CPPFLAGS += -DDEFECT_NO_EXCEPTIONS
  endif
endif                   # $(Exceptions_USED) == no
