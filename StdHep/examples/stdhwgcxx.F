      subroutine stdhwgcxxinit(nevt)
c
c  initialization for the herwig to stdhep C++ test
c
#include "CLHEP/StdHep/include/herwig64.inc"
#include "CLHEP/StdHep/include/stdlun.inc"

      external hwudat
      integer n
      integer istr,nevt
C
C initialize HEP logical units
      lnhwrt=23
      lnhrd=0
      lnhdcy=0
      lnhout=22
      lhwout=lnhout
      open(unit=lnhout,file='examHerwigToStdHep.lpt',status='new')
      call bookhist
      call cntcode(1)
C
C---max number of events this run
      maxev=nevt
C---process
      iproc=1500
C---beams
      pbeam1=900.
      pbeam2=900.
      part1='PBAR    '
      part2='P       '
C---initialise other common blocks
      call hwigin
C---user can reset parameters at this point,
C   otherwise values set in HWIGIN will be used.
      lrsud=0
      lwsud=0
      maxpr=1
      nrn(1)=106645411
      nrn(2)=135135175
      maxer=100
      tlout=15.
      ptmin=10.
      ptmax=80.
      emmin=40.
      emmax=80.
      q2min=1600.
      q2max=3600.
C---HIGGS mass
      rmass(201)=400.
C---compute parameter-dependent constants
      iprint = 2
      call hwuinc
      iprint = 1
C---call HWUSTA to make any particle stable
      call hwusta('PI0     ')
C---user's initial calculations
      call hwabeg
C---initialise elementary process
      call hweini
C          Fill Stdhep common block 1
        call stdflhwxsec
      return
      end

      subroutine stdhwgcxx
C---initialise event
        call hwuine
C---generate hard subprocess
        call hwepro
C---generate parton cascades
        call hwbgen
C---do heavy quark decays
        call hwdhob
C---do cluster hadronization
        call hwcfor
C---do cluster decay
        call hwcdec
C---do unstable particle decays
        call hwdhad
C---do heavy flavour decays
        call hwdhvy
C---add soft underlying event if needed
        call hwmevt
C---finalise event
        call hwufne
c---user's event analysis
        call hwanal
	call cntcode(2)
      return
      end

      subroutine stdhwgcxx_xsec
      call stdflhwxsec
      return
      end
      
      subroutine stdhwgcxxend
#include "CLHEP/StdHep/include/stdlun.inc"
C---terminate elementary process
      call hwefin
C---user's terminal calculations
      call hwaend
C          Fill Stdhep common block 1
      call stdflhwxsec
      call cntcode(3)
C...print histograms
      call houtpu(lnhout)
      call histdo
      close(unit=lnhout)
      close(unit=lnhwrt)
      return
      end
      
      subroutine cntcode(ii)
c
c  make a table of isthep values
c
#include "CLHEP/HepMC/include/stdhep.inc"
#include "CLHEP/StdHep/include/stdlun.inc"
      integer ii,i,ist,icnt(200)
      save icnt

      if(ii.eq.1)then
         do i=1,200
	   icnt(i)=0
	 enddo
      elseif(ii.eq.2)then
         do i=1,nhep
	   ist = isthep(i)
	   if(ist.le.200 .and. ist.gt.0) icnt(ist) = icnt(ist) + 1
	 enddo
      elseif(ii.eq.3)then
         write(lnhout,1001) 
	 do i=1,200
            write(lnhout,1002) i,icnt(i)
	 enddo
      else
      endif

      return
 1001 format(10x,'List of used isthep values')
 1002 format(' isthep ',i3,2x,i10)
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
