
      subroutine list_herwig_init(nevt)
c
c  initialization for the herwig C++ listing
c
#include "herwig65.inc"
      integer lnhwrt,lnhrd,lnhout,lnhdcy
      common/heplun/lnhwrt,lnhrd,lnhout,lnhdcy

      external hwudat
      integer n
      integer istr,nevt
C
C initialize HEP logical units
      lnhwrt=0
      lnhrd=0
      lnhdcy=0
      lnhout=22
      lhwout=lnhout
C      open(unit=lnhout,file='examHerwigToStdHep.lpt',status='new')
C
c      call hptrlsth
C
      return
      end
      
      subroutine get_list_size( isize )
c return the maximum size of herwig's particle list
#include "herwig65.inc"
      integer isize
      isize = NRES
      return
      end
      
       subroutine get_herwig_name( ihwg, id, name )
c ihwg is the index into herwig's short list
#include "herwig65.inc"
      integer id, ihwg
      character*8 name
      id = 0
      call HWUIDT(2,id,ihwg,name)
      return
      end
      
      subroutine list_herwig_end
      integer lnhwrt,lnhrd,lnhout,lnhdcy
      common/heplun/lnhwrt,lnhrd,lnhout,lnhdcy
C---terminate elementary process
c      call hwefin
C      close(unit=lnhout)
      return
      end

C----------------------------------------------------------------------
      subroutine hwabeg
C... user's routine for initialization
      end
      subroutine hwaend
C... user's routine for terminal calculations, histogram output, etc
      end
      subroutine hwanal
C... user's routine to analyse data from event
      end
C----------------------------------------------------------------------
