C -------------------------------------------------------------
C
      integer lnhwrt,lnhrd,lnhout,lnhdcy,lnhrdm,ixdrstr
      character*80 qqufile		! use this to set the QQ user decay file
      common/heplun/lnhwrt,lnhrd,lnhout,lnhdcy,lnhrdm(16)
      common/stdstr/ixdrstr(16)
      common/stdfnm/qqufile
      save /heplun/,/stdstr/
C
C -------------------------------------------------------------
