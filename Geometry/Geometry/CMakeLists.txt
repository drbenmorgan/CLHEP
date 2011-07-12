
set( pkginclude_HEADERS BasicVector3D.h
        		Normal3D.h     
        		Plane3D.h      
        		Point3D.h      
        		Transform3D.h  
        		Transform3D.icc
        		Vector3D.h )

# notice that defs.h is not referenced here
INSTALL (FILES ${pkginclude_HEADERS}  
         DESTINATION include/CLHEP/Geometry )

