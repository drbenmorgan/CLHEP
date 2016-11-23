
set( pkginclude_HEADERS atomic_int.h
                        keywords.h
        		memory.h
        		noncopyable.h )

# notice that defs.h is not referenced here
INSTALL (FILES ${pkginclude_HEADERS}  
         DESTINATION include/CLHEP/Utility )

# thread_local.h is a special case
CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/thread_local.in
                 ${CLHEP_BINARY_DIR}/CLHEP/Utility/thread_local.h @ONLY)
INSTALL ( FILES  ${CLHEP_BINARY_DIR}/CLHEP/Utility/thread_local.h 
         DESTINATION include/CLHEP/Utility )
