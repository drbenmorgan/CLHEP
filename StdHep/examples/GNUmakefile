#
# StdHep examples makefile
#
# for KCC:
# gmake LIBNAME=libCLHEP-KCC.1.8.0.0.a CXX=KCC
#
################################################################################ 

ifndef CXX
    CXX = g++
endif

ifndef LIBNAME
    LIBNAME = libCLHEP-1.9.0.2.a
endif

ifndef PythiaLIB
    PythiaLIB = $(LULIB)/pydata.o $(LULIB)/liblund.a $(LULIB)/libpydum.a
endif


################################################################################ 

UNAME = $(shell uname)
ifeq "$(UNAME)" "IRIX"
    IRIX6 = $(findstring 6,$(shell uname -r))
    ifeq "$(IRIX6)" "6"
	UNAME=IRIX64
    endif
endif

ifeq "$(UNAME)" "Linux"
    L22 = $(findstring 2.2,$(shell uname -r))
    ifeq "$(L22)" "2.2"
	UNAME=Linux22
    endif
endif

ifndef DEBUG
    DEBUG = none
    DFLG =
    SFX =
else
    DFLG = $(DEBUG)
    SFX = _g
endif

CXX = g++
##CXX = CC

ifeq "$(UNAME)" "IRIX"
    CC=cc
    CPP = /lib/cpp
    F77=f77
    KPPFLAGS= -C -P -DIRIX -DUNIX
    CFLAGS= $(DFLG)
    FFLAGS= $(DFLG)
    LCXX = -lftn
endif
ifeq "$(UNAME)" "IRIX64"
    CC=cc
    CPP = /lib/cpp
    F77=f77
    CFLAGS= $(DFLG) -n32
    FFLAGS= $(DFLG) -n32
    KPPFLAGS= -C -P -DIRIX -DUNIX
    LCXX = -lftn -lm
endif
ifeq "$(UNAME)" "Linux"
    CC=gcc
    CPP=gcc -E
    F77=g77
    CFLAGS= $(DFLG) 
    FFLAGS= $(DFLG) -fno-second-underscore
    KPPFLAGS= -C -P -DLinux -DUNIX
    LCXX = -lg2c
    LOCAL = -lnsl
    ## setup egcs gets this wrong, so fix it here
    CPLUS_INCLUDE_PATH = $(EGCS_DIR)/include/g++
endif
ifeq "$(UNAME)" "Linux22"
    CC=/usr/bin/gcc
    CPP=/usr/bin/gcc -E
    F77=/usr/bin/g77
    CFLAGS= $(DFLG)
    FFLAGS= $(DFLG) -fno-second-underscore
    KPPFLAGS= -C -P -DLinux -DUNIX
    LCXX = -lg2c
    LOCAL = -lnsl
endif
ifeq "$(UNAME)" "OSF1"
    CC=cc
    CPP = /usr/lib/cpp
    F77=f77
    CFLAGS= $(DFLG) 
    FFLAGS= $(DFLG) -fpe2 -check underflow -check overflow
    KPPFLAGS= -C -P -DOSF1 -DUNIX
    LCXX = -lfor -lUfor
endif
ifeq "$(UNAME)" "SunOS"
    CC=/opt/SUNWspro/bin/cc
    CPP = /usr/ccs/lib/cpp
    F77=f77
    CFLAGS= $(DFLG)
    FFLAGS= $(DFLG)
    KPPFLAGS= -C -P -DSunOS -DUNIX
    LOCAL= -L/opt/SUNWspro/lib -lm -lnsl -lsocket -lF77 -lM77 -ldbxFintr -lsunmath -R/opt/SUNWspro/lib
endif

INCDIR = -I$(CLHEP_DIR)/include -I$(LUND_DIR)/src/inc -I$(HERWIG_DIR)/src 
CPPFLGS = $(KPPFLAGS) $(INCDIR)
CXXFLAGS = $(DFLG) $(INCDIR)

STDHEPLIB = $(CLHEP_DIR)/lib/$(LIBNAME)


PYTOBJS = examPythiaToStdHep$(SFX).o stdpytcxx$(SFX).o dummy$(SFX).o \
          lunhep$(SFX).o lutran$(SFX).o stdflpyxsec$(SFX).o \
	  bookhist$(SFX).o analyzeEvent$(SFX).o
HWGOBJS = examHerwigToStdHep$(SFX).o stdhwgcxx$(SFX).o dummy$(SFX).o \
          hwghep$(SFX).o hwtran$(SFX).o stdflhwxsec$(SFX).o \
	  bookhist$(SFX).o analyzeEvent$(SFX).o
READOBJS = dummy$(SFX).o bookhist$(SFX).o analyzeEvent$(SFX).o

PYTXDROBJS =  $(HWGOBJS) \
          RunXDR$(SFX).o StdHepXDR$(SFX).o
HWGXDROOBJS = $(HWGOBJS) \
          RunXDR$(SFX).o StdHepXDR$(SFX).o
RXDROBJS =  readMultipleXDR$(SFX).o readcxx$(SFX).o \
            RunXDR$(SFX).o StdHepXDR$(SFX).o
RFOBJS =  readStdHepXDR$(SFX).o readStdHepXDRinit$(SFX).o \
            RunXDR$(SFX).o StdHepXDR$(SFX).o

#------------------------------------------

all: examPythiaToStdHep examHerwigToStdHep readPythia readPythiaHerwig

xdr: examPythiaToStdHepXDR examHerwigToStdHepXDR readMultipleXDR readStdHepXDR

examPythiaToStdHep: $(STDHEPLIB) $(PYTOBJS)
	$(CXX) -o $@  \
	$(PYTOBJS) \
	$(STDHEPLIB) \
        $(PythiaLIB) \
	$(CRNLIB)/libpacklib.a $(LCXX) $(LOCAL)

examHerwigToStdHep: $(STDHEPLIB) $(HWGOBJS)
	$(CXX) -o $@ \
	$(HWGOBJS) \
	$(HERWIG_DIR)/lib/hwudat.o \
	$(STDHEPLIB) \
	-L$(HERWIG_DIR)/lib -lherwig -lherdum \
	$(CRNLIB)/libpacklib.a $(LCXX) $(LOCAL)

examPythiaToStdHepXDR: $(STDHEPLIB) $(PYTOBJS)
	$(CXX) -o $@  \
	$(PYTOBJS) \
	$(STDHEPLIB) \
        $(PythiaLIB) \
	libFmcfioCXX$(SFX).a \
	$(CRNLIB)/libpacklib.a $(LCXX) $(LOCAL)

examHerwigToStdHepXDR: $(STDHEPLIB) $(HWGOBJS)
	$(CXX) -o $@ \
	$(HWGOBJS) \
	$(HERWIG_DIR)/lib/hwudat.o \
	$(STDHEPLIB) \
	libFmcfioCXX$(SFX).a \
	-L$(HERWIG_DIR)/lib -lherwig -lherdum \
	$(CRNLIB)/libpacklib.a $(LCXX) $(LOCAL)

readPythia:  readPythia$(SFX).o $(READOBJS) $(STDHEPLIB) 
	$(CXX) -o $@ readPythia$(SFX).o $(READOBJS) \
	$(STDHEPLIB) \
	$(CRNLIB)/libpacklib.a $(LCXX) $(LOCAL)

readPythiaHerwig:  readPythiaHerwig$(SFX).o $(READOBJS) $(STDHEPLIB) 
	$(CXX) -o $@ readPythiaHerwig$(SFX).o $(READOBJS) \
	$(STDHEPLIB) \
	$(CRNLIB)/libpacklib.a $(LCXX) $(LOCAL)

readMultipleXDR:  $(STDHEPLIB) $(RXDROBJS)
	$(CXX) -o $@ $(RXDROBJS) \
	$(STDHEPLIB) \
	libFmcfioCXX$(SFX).a \
	$(CRNLIB)/libpacklib.a $(LCXX) $(LOCAL)

readStdHepXDR: $(STDHEPLIB) $(RFOBJS)
	$(CXX) -o $@ $(RFOBJS) \
	$(STDHEPLIB) \
	libFmcfioCXX$(SFX).a \
	$(CRNLIB)/libpacklib.a $(LCXX) $(LOCAL)

cleanobjs:
	rm -f *.o *.f
	rm -rf ti_files

clean:
	rm -f examPythiaToStdHep examHerwigToStdHep
	rm -f readPythia readPythiaHerwig
	rm -f examPythiaToStdHepXDR examHerwigToStdHepXDR
	rm -f readMultipleXDR readStdHepXDR
	rm -f *.bak *.o *.f
	rm -rf ti_files
	rm -f log.*

#------------------------------------------

run: runPythiaToStdHep runHerwigToStdHep runReadPythia runReadPythiaHerwig

examPythiaToStdHep.dat: runPythiaToStdHep

examHerwigtoStdHep.dat: runHerwigToStdHep

runPythiaToStdHep: examPythiaToStdHep
	-test -e examPythiaToStdHep.out  && \
		mv -f examPythiaToStdHep.out examPythiaToStdHep.out.bak
	-test -e examPythiaToStdHep.lpt  && \
		mv -f examPythiaToStdHep.lpt examPythiaToStdHep.lpt.bak
	-test -e examPythiaToStdHep.dat  && \
		mv -f examPythiaToStdHep.dat examPythiaToStdHep.dat.bak
	./examPythiaToStdHep > examPythiaToStdHep.out

runHerwigToStdHep: examHerwigToStdHep
	-test -e examHerwigToStdHep.out  && \
		mv -f examHerwigToStdHep.out examHerwigToStdHep.out.bak
	-test -e examHerwigToStdHep.lpt  && \
		mv -f examHerwigToStdHep.lpt examHerwigToStdHep.lpt.bak
	-test -e examHerwigtoStdHep.dat  && \
		mv -f examHerwigtoStdHep.dat examHerwigtoStdHep.dat.bak
	./examHerwigToStdHep > examHerwigToStdHep.out
	rm -f fort.88

runReadPythia: readPythia
	-test -e readPythia.out  && \
		mv -f readPythia.out readPythia.out.bak
	./readPythia > readPythia.out

runReadPythiaHerwig: readPythiaHerwig
	-test -e readPythiaHerwig.out  && \
		mv -f readPythiaHerwig.out readPythiaHerwig.out.bak
	./readPythiaHerwig > readPythiaHerwig.out


runxdr: xdr

#------------------------------------------

.SUFFIXES : 			# cancel implicit rules
.SUFFIXES : .o .c .cc .F .inc .h .hh 

%.o: %.F
	$(CPP) $(CPPFLGS) $< > $*.f
	$(F77) $(FFLAGS) -c $*.f

%_g.o: %.F
	$(CPP) $(CPPFLGS) $< > $*.f
	$(F77) $(FFLAGS) -c -o $@ $*.f

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $<

%_g.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<
