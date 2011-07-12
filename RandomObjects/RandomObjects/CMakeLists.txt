
set( pkginclude_HEADERS RandMultiGauss.h 
        		RandomVector.h   
        		RandomVector.icc )

# notice that defs.h is not referenced here
INSTALL (FILES ${pkginclude_HEADERS}  
         DESTINATION include/CLHEP/RandomObjects )

