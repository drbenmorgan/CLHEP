       subroutine readcxx()

c include stdhep.inc so the linker will resolve the reference from mcfio
#include "CLHEP/HepMC/include/stdhep.inc"
#include "CLHEP/HepMC/include/hepev4.inc"

      call bookhist

      return
      end
