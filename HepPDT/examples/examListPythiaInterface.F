      subroutine list_pythia
C
C     list jetset particle definitions
C
#include "pydat1.inc"

      INTEGER LNHOUT
C
      lnhout=22
      MSTU(11)=LNHOUT
      OPEN(UNIT=LNHOUT,FILE='examListPythia.lpt',STATUS='NEW')
C
C... 
      call pylist(11)
C...enable pylist(12) if you need a new pythia decay table
C      call pylist(12)
C
C
c...close output file
      CLOSE(UNIT=LNHOUT)
      return
      END

