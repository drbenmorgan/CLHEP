      subroutine list_isajet_init
C   
C     JTDKY = +/- unit number for decay table file.    
C                 If it is negative, decay table is not printed.   
C     JTEVT = +/- unit number for output event file.   
C                 If it is negative, only stable particles are written on it. 
C     JTCOM =     unit number for command file.    
C     JTLIS =     unit number for listing. 
C   
      IMPLICIT NONE 

C   
      integer istr,nevt,itotal
      INTEGER JTDKY,JTEVT,JTCOM,JTLIS,IFL,ILOOP,IPRT,LOK,ILOOP2
      INTEGER INDEC,INDEC2
      CHARACTER*132 ISADEC
      LOGICAL OK,DONE
      SAVE ILOOP,JTDKY,JTEVT,JTCOM,JTLIS

      EXTERNAL ALDATA
C   
C          Initialize ISAJET    
C   
      JTDKY=-1
      JTEVT=23
      JTCOM=21
      JTLIS=6
      nevt=1000
      itotal=0
C  point to standard decay tables
      CALL GETENV( 'ISAJET_DIR', ISADEC )
      IF ( ISADEC .EQ. ' ' ) THEN
         ISADEC = 'isadecay.dat'
      ELSE
         INDEC   = INDEX ( ISADEC , ' ' )
         ISADEC(INDEC:INDEC+13)  = '/isadecay.dat'
         INDEC2  = INDEX ( ISADEC , ' ' ) - 1
c         print *,'looking for ',ISADEC(:INDEC2)
      ENDIF
      OPEN(UNIT=1,FILE=ISADEC,STATUS='OLD')
      CALL ISAINI(JTDKY,JTEVT,JTCOM,JTLIS)  
      IPRT=1
C   
C print list of defined particles and their translations
C    (you have to call ISAINI first)
C use bogus masses for 4th generation quarks so we can see their definitions
C
c      CALL PRTLST(JTLIS,200.,220.)
C

      return
      END 

      subroutine get_label( id, lb)
      
      integer id
      character*8 LB,LABEL

      lb = '    '
      
      if ( id.ne.0) then
         lb = LABEL(id)
      endif

      return
      end
