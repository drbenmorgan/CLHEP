c
c Matt.Dobbs@Cern.CH, December 1999
c EXTERNAL statement links PYDATA on most machines.
c (Often necessary for the initialization of Pythia)
c
c force include of stdhep common blocks
      subroutine initpydata
#include "CLHEP/HepMC/include/stdhep.inc"
#include "CLHEP/HepMC/include/hepev4.inc"
      EXTERNAL PYDATA
      return
      end


