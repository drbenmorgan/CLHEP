
set( pkginclude_HEADERS GlobalPhysicalConstants.h
			GlobalSystemOfUnits.h
			PhysicalConstants.h
			SystemOfUnits.h	)

# notice that defs.h is not referenced here
INSTALL (FILES ${pkginclude_HEADERS} 
         DESTINATION include/CLHEP/Units )

