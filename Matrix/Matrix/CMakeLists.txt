
set( pkginclude_HEADERS DiagMatrix.h   
			DiagMatrix.icc 
			GenMatrix.h    
			GenMatrix.icc  
			Matrix.h       
			Matrix.icc     
			Pile.h         
			SymMatrix.h    
			SymMatrix.icc  
			Vector.h       
			Vector.icc )


# notice that defs.h is not referenced here
INSTALL (FILES ${pkginclude_HEADERS}  
         DESTINATION include/CLHEP/Matrix )

