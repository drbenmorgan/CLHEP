
set( pkginclude_HEADERS Evaluator.h )

# notice that defs.h is not referenced here
INSTALL (FILES ${pkginclude_HEADERS}  
         DESTINATION include/CLHEP/Evaluator )

