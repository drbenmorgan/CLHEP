#
# HepMC examples makefile
#
# use: gmake [INCDIR= ] [CXX= ] [LIBNAME= ] all
#      gmake [INCDIR= ] [CXX= ] [LIBNAME= ] run
#
# other variables:
#      [PythiaLIB= ]
#      [HerwigLIB= ]
#
################################################################################ 

PLATFORM=$(shell uname)
ifeq "$(PLATFORM)" "IRIX"
    IRIX6 = $(findstring 6,$(shell uname -r))
    ifeq "$(IRIX6)" "6"
	PLATFORM=IRIX64
    endif
endif
################################################################################ 

ifndef DEBUG
    SFX =
else
    SFX = _g
endif

################################################################################ 

  CXX = g++
  INCDIR    = -I$(CLHEP_DIR)/include
  HepMCinc  = $(INCDIR)/CLHEP/HepMC
  PythiaLIB = $(LULIB)/pydata.o $(LULIB)/liblund.a $(LULIB)/libpydum.a
  HerwigLIB = $(HERWIG_DIR)/lib/libherwig.a $(HERWIG_DIR)/lib/libherdum.a $(HERWIG_DIR)/lib/timel.o
  LIBNAME = $(CLHEP_DIR)/lib/libCLHEP-1.9.1.1.a


################################################################################ 
ifeq "$(PLATFORM)" "HP-UX"
    F77=f77
    F77FLAG= 
    FLAGS =  
    LINK_LIBS        = -lg2c -lftn -lf
endif
ifeq "$(PLATFORM)" "IRIX"
    F77=f77
    F77FLAG= 
    FLAGS =  
    LINK_LIBS     = -lg2c -lftn
endif
ifeq "$(PLATFORM)" "IRIX64"
    F77=f77
    F77FLAG=  -n32
    FLAGS =  
    LINK_LIBS     = -lg2c -lftn
endif
ifeq "$(PLATFORM)" "Linux"
    F77=g77
    F77FLAG=  -fno-second-underscore
ifeq "$(CXX)" "g++"
    FLAGS =  -O -ansi -pedantic-errors -Wall
endif
    LOCAL = -lnsl
    LINK_LIBS     = -lg2c 
endif
ifeq "$(PLATFORM)" "OSF1"
    F77=f77
    F77FLAG=  -fpe2 -check underflow -check overflow
    FLAGS =  
    LINK_LIBS = -lfor -lUfor
endif
ifeq "$(PLATFORM)" "SunOS"
    F77=f77
    F77FLAG= 
    FLAGS =  
    LOCAL= -L/opt/SUNWspro/lib -lm -lnsl -lsocket -lF77 -lM77 -ldbxFintr -lsunmath -R/opt/SUNWspro/lib
    LINK_LIBS     = -lg2c 
endif

################################################################################ 

FFLAGS = $(filter-out -fPIC, $(F77FLAG))

HDRS     = $(wildcard $(HepMCinc)/*.h) $(wildcard *.h)
examples = $(addsuffix .exe,$(basename $(wildcard example*.cc)))
examples += $(addsuffix .exe,$(basename $(wildcard test*.cc)))
## these examples use ReadHepMC and WriteHepMC
runList = runPythiaWriteHepMC runReadHepMC runTestMethods
## these are the original examples and use IO_Ascii where appropriate
runListAscii = run_UsingIterators  \
               run_MyPythiaWithEventSelection run_MyPythiaOnlyToHepMC \
	       run_MyPythia run_EventSelection
initpydata_OBJ= initpydata$(SFX).o
Ascii_OBJ = IO_Ascii$(SFX).o

################################################################################ 

all: $(examples)

run: $(runList) $(runListAscii)

example_MyHerwig.exe: example_MyHerwig$(SFX).o
	@echo "Building $@ ..."
	$(CXX) $(FLAGS) example_MyHerwig$(SFX).o \
               $(LIBNAME) \
	       $(HerwigLIB) $(LINK_LIBS) -o $@

example_MyPythia.exe: example_MyPythia$(SFX).o $(initpydata_OBJ) $(Ascii_OBJ)
	@echo "Building $@ ..."
	$(CXX) $(FLAGS) example_MyPythia$(SFX).o $(initpydata_OBJ) $(Ascii_OBJ)  \
               $(LIBNAME) \
	       $(PythiaLIB) $(LINK_LIBS) -o $@

example_MyPythiaOnlyToHepMC.exe: example_MyPythiaOnlyToHepMC$(SFX).o $(initpydata_OBJ)
	@echo "Building $@ ..."
	$(CXX) $(FLAGS) example_MyPythiaOnlyToHepMC$(SFX).o  $(initpydata_OBJ)  \
               $(LIBNAME) \
	       $(PythiaLIB) $(LINK_LIBS) -o $@

example_MyPythiaWithEventSelection.exe: example_MyPythiaWithEventSelection$(SFX).o  $(initpydata_OBJ)
	@echo "Building $@ ..."
	$(CXX) $(FLAGS) example_MyPythiaWithEventSelection$(SFX).o  $(initpydata_OBJ)  \
               $(LIBNAME) \
	       $(PythiaLIB) $(LINK_LIBS) -o $@

example_EventSelection.exe: example_EventSelection$(SFX).o $(Ascii_OBJ)
	@echo "Building $@ ..."
	$(CXX) $(FLAGS) example_EventSelection$(SFX).o $(Ascii_OBJ)  \
               $(LIBNAME) \
	       $(LINK_LIBS) -o $@

example_UsingIterators.exe: example_UsingIterators$(SFX).o $(initpydata_OBJ) $(Ascii_OBJ)
	@echo "Building $@ ..."
	$(CXX) $(FLAGS) example_UsingIterators$(SFX).o $(initpydata_OBJ) $(Ascii_OBJ) \
               $(LIBNAME) \
	       $(PythiaLIB) $(LINK_LIBS) -o $@

examplePythiaWriteHepMC.exe: examplePythiaWriteHepMC$(SFX).o $(initpydata_OBJ)
	@echo "Building $@ ..."
	$(CXX) $(FLAGS) examplePythiaWriteHepMC$(SFX).o $(initpydata_OBJ) \
               $(LIBNAME) \
	       $(PythiaLIB) $(LINK_LIBS) -o $@

exampleReadHepMC.exe: exampleReadHepMC$(SFX).o
	@echo "Building $@ ..."
	$(CXX) $(FLAGS) exampleReadHepMC$(SFX).o  \
               $(LIBNAME) \
	       $(LINK_LIBS) -o $@

test_MakeUsingIteratorsInput.exe: test_MakeUsingIteratorsInput$(SFX).o $(Ascii_OBJ) $(initpydata_OBJ)
	@echo "Building $@ ..."
	$(CXX) $(FLAGS) test_MakeUsingIteratorsInput$(SFX).o $(Ascii_OBJ) $(initpydata_OBJ) \
               $(LIBNAME) \
		$(PythiaLIB) \
	       $(LINK_LIBS) -o $@

testMethods.exe: testMethods$(SFX).o  $(initpydata_OBJ)
	@echo "Building $@ ..."
	$(CXX) $(FLAGS) testMethods$(SFX).o  $(initpydata_OBJ)  \
               $(LIBNAME) \
	       $(PythiaLIB) $(LINK_LIBS) -o $@

cleanobjs:
	rm -f *.o

clean:
	rm -f *.o
	rm -f *.exe
	rm -f *.bak

test:
	@echo "CXX: "$(CXX)
	@echo "INCDIR: "$(INCDIR)
	@echo "HepMCinc: "$(HepMCinc)
	@echo "PythiaLIB: "$(PythiaLIB)
	@echo "LIBNAME: "$(LIBNAME)

################################################################################ 

run_EventSelection: example_EventSelection.exe  
	-test -e example_EventSelection.out && \
		mv -f example_EventSelection.out example_EventSelection.out.bak	
	example_EventSelection.exe > example_EventSelection.out

run_MyPythia: example_MyPythia.exe  
	-test -e example_MyPythia.out && \
		mv -f example_MyPythia.out example_MyPythia.out.bak	
	example_MyPythia.exe > example_MyPythia.out

run_MyPythiaOnlyToHepMC: example_MyPythiaOnlyToHepMC.exe  
	-test -e example_MyPythiaOnlyToHepMC.out && \
		mv -f example_MyPythiaOnlyToHepMC.out example_MyPythiaOnlyToHepMC.out.bak	
	example_MyPythiaOnlyToHepMC.exe > example_MyPythiaOnlyToHepMC.out

run_MyPythiaWithEventSelection: example_MyPythiaWithEventSelection.exe  
	-test -e example_MyPythiaWithEventSelection.out && \
		mv -f example_MyPythiaWithEventSelection.out example_MyPythiaWithEventSelection.out.bak	
	example_MyPythiaWithEventSelection.exe > example_MyPythiaWithEventSelection.out

run_UsingIterators: example_UsingIterators.exe  
	-test -e example_UsingIterators.txt && \
		mv -f example_UsingIterators.txt example_UsingIterators.txt.bak	
	test_MakeUsingIteratorsInput.exe
	-test -e example_UsingIterators.out && \
		mv -f example_UsingIterators.out example_UsingIterators.out.bak	
	example_UsingIterators.exe > example_UsingIterators.out

runPythiaWriteHepMC: examplePythiaWriteHepMC.exe  
	-test -e examplePythiaWriteHepMC.dat && \
		mv -f examplePythiaWriteHepMC.dat examplePythiaWriteHepMC.dat.bak	
	-test -e examplePythiaWriteHepMC.out && \
		mv -f examplePythiaWriteHepMC.out examplePythiaWriteHepMC.out.bak	
	examplePythiaWriteHepMC.exe > examplePythiaWriteHepMC.out

runReadHepMC: exampleReadHepMC.exe  
	-test -e exampleReadHepMC.out && \
		mv -f exampleReadHepMC.out exampleReadHepMC.out.bak	
	-test -e exampleReadHepMC.dat && \
		mv -f exampleReadHepMC.dat exampleReadHepMC.dat.bak	
	exampleReadHepMC.exe > exampleReadHepMC.out

runTestMethods: testMethods.exe  
	-test -e testMethods.out && mv -f testMethods.out testMethods.out.bak	
	testMethods.exe > testMethods.out

################################################################################ 

.SUFFIXES : 			# cancel implicit rules
.SUFFIXES : .o .cc .F .inc .h .hh 

%.o: %.F
	@echo "Compiling $< with $(F77) ..."
	$(F77) $(FFLAGS) $(INCDIR) -c $< -o $@

%_g.o: %.F
	@echo "Compiling $< with $(F77) ..."
	$(F77) $(DEBUG) $(FFLAGS) $(INCDIR) -c $< -o $@

%.o: %.cc $(HDRS)
	@echo "Compiling $< with $(CXX) ..."
	$(CXX)  $(FLAGS) $(INCDIR) -c $< -o $@

%_g.o: %.cc $(HDRS)
	@echo "Compiling $< with $(CXX) ..."
	$(CXX) $(DEBUG) $(FLAGS) $(INCDIR) -c $< -o $@
