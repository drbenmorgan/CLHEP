# 
# $Id: GNUmakefile,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
#
# makefile for HepPDT examples
#
# Usage:  gmake 
# Options:  PDTLIB=<CLHEP library> 
#           INCDIR=<path to clhep includes>
#           CXX=<C++ compiler> 
#                 You can add optional compiler flags to CXX

ifndef DEBUG
    DEBUG = none
    DFLG =
    SFX =
else
    DFLG = $(DEBUG)
    SFX = _g
endif

ifndef CXX
    CXX = g++
endif

ifndef PDTLIB
    PDTLIB = ../../../lib/libCLHEP-g++.1.8.0.0.a
endif

ifndef INCDIR
    INCDIR = -I../../../include
endif

AR=ar
ARFLG = -urs

CXXFLAGS = $(DFLG) $(INCDIR)
ifeq "$(CXX)" "KCC"
  CXXFLAGS +=  +K0 -O0 --no_implicit_include --one_per
  PDTLIB = ../../../lib/libCLHEP-KCC.1.7.0.0.a
endif

SOURCE = $(wildcard *.cc)

include $(SOURCE:.cc=.d)

#------------------------------------------

all: build_test run_test

test:  run_test

build_test: examReadPDG examReadPythia examReadEvtGen examReadQQ \
            examMyPDT examDMF

examMyPDT: examMyPDT.o $(PDTLIB)
	$(CXX) $(CXXFLAGS) -o $@ examMyPDT.o \
		$(PDTLIB) -lm
	rm -rf ti_files

examDMF: ModeA$(SFX).o ModeB$(SFX).o examDMF.o $(PDTLIB) 
	$(CXX) $(CXXFLAGS) -o $@ examDMF.o \
		 ModeA$(SFX).o ModeB$(SFX).o \
		 $(PDTLIB) -lm
	rm -rf ti_files

examReadPDG: examReadPDG.o $(PDTLIB)
	$(CXX) $(CXXFLAGS) -o $@ examReadPDG.o \
		$(PDTLIB) -lm
	rm -rf ti_files

examReadPythia: examReadPythia.o $(PDTLIB)
	$(CXX) $(CXXFLAGS) -o $@ examReadPythia.o \
		$(PDTLIB) -lm
	rm -rf ti_files

examReadQQ: examReadQQ.o $(PDTLIB)
	$(CXX) $(CXXFLAGS) -o $@ examReadQQ.o \
		$(PDTLIB) -lm $(PDTLIB)
	rm -rf ti_files

examReadEvtGen: examReadEvtGen.o $(PDTLIB)
	$(CXX) $(CXXFLAGS) -o $@ examReadEvtGen.o \
		$(PDTLIB) -lm
	rm -rf ti_files

run_test: examReadPDG examReadPythia examReadEvtGen examMyPDT examReadQQ
	examReadPDG  > examReadPDG.log
	diff examReadPDG.out examReadPDG.out.save
	examReadPythia  > examReadPythia.log
	diff examReadPythia.out examReadPythia.out.save
	examReadEvtGen  > examReadEvtGen.log
	diff examReadEvtGen.out examReadEvtGen.out.save
	examMyPDT > examMyPDT.log
	diff examMyPDT.out examMyPDT.out.save
	examReadQQ  > examReadQQ.log
	diff examReadQQ.out examReadQQ.out.save

cleanobjs:
	rm -f *.o
	rm -f *.d
	rm -rf ti_files

clean:
	rm -f *.o
	rm -f *.d
	rm -rf ti_files
	rm -f examReadPDG examReadPythia examReadEvtGen 
	rm -f examMyPDT examDMF examReadQQ
	rm -f *.out *.log

#------------------------------------------

.PHONY:  clean cleanobjs

.SUFFIXES :             # cancel implicit rules
.SUFFIXES : .o .cc .cpp

%.d: %.cc
	@$(SHELL) -ec '$(CXX) -M $(CXXFLAGS) $< | sed '\''s/$*.o/& $@/g'\'' > $@'

%.o: %.cc %.d
	$(CXX) $(CXXFLAGS) -c $<

%_g.o: %.cc %.d
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.d: %.cpp
	@$(SHELL) -ec '$(CXX) -M $(CXXFLAGS) $< | sed '\''s/$*.o/& $@/g'\'' > $@'

%.o: %.cpp %.d
	$(CXX) $(CXXFLAGS) -c $<

%_g.o: %.cpp %.d
	$(CXX) $(CXXFLAGS) -c -o $@ $<
