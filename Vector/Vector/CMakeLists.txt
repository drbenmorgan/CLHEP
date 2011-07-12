
set( pkginclude_HEADERS AxisAngle.h
			AxisAngle.icc
			Boost.h	
			Boost.icc
			BoostX.h
			BoostX.icc
			BoostY.h
			BoostY.icc
			BoostZ.h
			BoostZ.icc
			EulerAngles.h
			EulerAngles.icc
			LorentzRotation.h
			LorentzRotation.icc
			LorentzVector.h
			LorentzVector.icc
			Rotation.h
			Rotation.icc
			RotationInterfaces.h
			RotationInterfaces.icc
			RotationX.h
			RotationX.icc
			RotationY.h
			RotationY.icc
			RotationZ.h
			RotationZ.icc
			Sqr.h	
			ThreeVector.h
			ThreeVector.icc
			TwoVector.h
			TwoVector.icc
			ZMxpv.h )

# notice that defs.h is not referenced here
INSTALL (FILES ${pkginclude_HEADERS}  
         DESTINATION include/CLHEP/Vector )

