      subroutine bookhist
C--- book histograms used by the examples
C
      implicit none
C---   The HBOOK common
      real hmemor
      common/pawc/hmemor(50000)
C---   Setup the HBOOK memory limit.
      call hlimit(50000)
C---   Book histograms.
C      call hbook1(10,'STDHEP: cross-section',100,0.,100.,0.)
      call hbook1(11,'NEVHEP',100,0.0,100.0,0.)
      call hbook1(12,'NHEP',100,0.,200.,0.)
      call hbook1(13,'IDHEP',100,0.,100.,0.)
      call hbook1(14,'ISTHEP',100,0.,100.,0.)
      call hbook1(15,'JMOHEP(1,)',100,0.,1000.,0.)
      call hbook1(16,'JMOHEP(2,)',100,0.,1000.,0.)
      call hbook1(17,'JDAHEP(1,)',100,0.,1000.,0.)
      call hbook1(18,'JDAHEP(2,)',100,0.,1000.,0.)
      call hbook1(21,'PHEP(1,)',100,-100.,100.,0.)
      call hbook1(22,'PHEP(2,)',100,-100.,100.,0.)
      call hbook1(23,'PHEP(3,)',100,-100.,100.,0.)
      call hbook1(24,'PHEP(4,)',100,-100.,100.,0.)
      call hbook1(25,'PHEP(5,)',100,-100.,100.,0.)
      call hbook1(26,'VHEP(1,)',10,-1.,1.,0.)
      call hbook1(27,'VHEP(2,)',10,-1.,1.,0.)
      call hbook1(28,'VHEP(3,)',10,-1.,1.,0.)
      call hbook1(29,'VHEP(4,)',10,0.,1.,0.)
      call hbook1(30,'StdHep: collisions',20,0.,10.,0.)
      call hbook1(31,'vertex x',10,-1.,1.,0.)
      call hbook1(32,'vertex y',10,-1.,1.,0.)
      call hbook1(33,'vertex z',10,-1.,1.,0.)
      call hbook1(34,'vertex t',10,0.,1.,0.)
      return
      end

