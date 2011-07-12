
set( pkginclude_HEADERS ZMerrno.h      
        		ZMerrno.icc    
        		ZMexAction.h   
        		ZMexClassInfo.h
        		ZMexClassInfo.icc
        		ZMexHandler.h  
        		ZMexHandler.icc
        		ZMexLogResult.h
        		ZMexLogger.h   
        		ZMexSeverity.h 
        		ZMexception.h  
        		ZMexception.icc
        		ZMthrow.h      
        		arch_spec_Exceptions.mk
        		link_Exceptions.mk )
 
# notice that defs.h is not referenced here
INSTALL (FILES ${pkginclude_HEADERS}  
         DESTINATION include/CLHEP/Exceptions )

