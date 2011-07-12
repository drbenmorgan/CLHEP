
set( pkginclude_HEADERS itos.h )

# notice that defs.h is not referenced here
INSTALL (FILES ${pkginclude_HEADERS}  
         DESTINATION include/CLHEP/Cast )

