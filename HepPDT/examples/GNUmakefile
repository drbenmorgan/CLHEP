# 
# $Id: GNUmakefile,v 1.2.2.7 2004/11/30 20:08:39 garren Exp $
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
    PDTLIB =  $(CLHEP_DIR)/lib/libCLHEP-HepPDT-2.0.1.2.a
endif

ifndef INCDIR
    INCDIR = -I$(CLHEP_DIR)/include
endif

ifdef HERWIG_DIR
    INCDIR += -I$(HERWIG_DIR)/src
endif

ifndef F77
    F77 = g77
endif

ifndef FFLAGS
    FFLAGS = $(DFLG) -fno-second-underscore $(INCDIR)
endif

AR=ar
ARFLG = -urs

CXXFLAGS = $(DFLG) $(INCDIR)

SOURCE = $(wildcard *.cc)

include $(SOURCE:.cc=.d)

#------------------------------------------

all: build_test run_test

list: examListHerwig examListIsajet

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

examListHerwig: examListHerwig.o examListHerwigInterface.o $(PDTLIB)
	$(CXX) $(CXXFLAGS) -o $@ \
		examListHerwig.o examListHerwigInterface.o \
		$(HERWIG_DIR)/lib/hwudat.o \
		-L$(HERWIG_DIR)/lib -lherwig -lherdum \
		$(PDTLIB) -lm -lg2c
	rm -rf ti_files

examListIsajet: examListIsajet.o examListIsajetInterface.o $(PDTLIB)
	$(CXX) $(CXXFLAGS) -o $@ \
		examListIsajet.o examListIsajetInterface.o \
		$(ISAJET_DIR)/isajet.a \
		$(PDTLIB) -lm -lg2c
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
	rm -f examMyPDT examDMF examReadQQ examListHerwig examListIsajet
	rm -f *.out *.log


#------------------------------------------

.PHONY:  clean cleanobjs

.SUFFIXES :             # cancel implicit rules
.SUFFIXES : .o .cc .cpp .F .inc .h .hh

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

%.o: %.F
	$(F77) $(FFLAGS) -c -o $@ $<
	
%_g.o: %.F
	$(F77) $(FFLAGS) -c -o $@ $<
 
