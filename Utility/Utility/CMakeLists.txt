
set( pkginclude_HEADERS keywords.h
        		memory.h
        		noncopyable.h
        		type_traits.h )

# notice that defs.h is not referenced here
INSTALL (FILES ${pkginclude_HEADERS}  
         DESTINATION include/CLHEP/Utility )

