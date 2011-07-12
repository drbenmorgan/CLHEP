
set( pkginclude_HEADERS  ZMhandleTo.h     
        		 ZMhandleTo.icc   
        		 ZMuseCount.h     
        		 ZMuseCount.icc )

# notice that defs.h is not referenced here
INSTALL (FILES ${pkginclude_HEADERS}  
         DESTINATION include/CLHEP/RefCount )

