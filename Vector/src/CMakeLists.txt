
set ( Vector_source_list    AxisAngle.cc
			     Boost.cc
			     BoostX.cc
			     BoostY.cc
			     BoostZ.cc
			     EulerAngles.cc
			     LorentzRotation.cc
			     LorentzRotationC.cc
			     LorentzRotationD.cc
			     LorentzVector.cc
			     LorentzVectorB.cc
			     LorentzVectorC.cc
			     LorentzVectorK.cc
			     LorentzVectorL.cc
			     LorentzVectorR.cc
			     Rotation.cc
			     RotationA.cc
			     RotationC.cc
			     RotationE.cc
			     RotationIO.cc
			     RotationInterfaces.cc
			     RotationL.cc
			     RotationP.cc
			     RotationX.cc
			     RotationY.cc
			     RotationZ.cc
			     SpaceVector.cc
			     SpaceVectorD.cc
			     SpaceVectorP.cc
			     SpaceVectorR.cc
			     ThreeVector.cc
			     ThreeVectorR.cc
			     TwoVector.cc
			     ZMinput.cc
			     ZMxpv.cc )
# RotationXYZ is empty 
# Skip it on MacOSX so ranlib won't complain
if( ${CMAKE_SYSTEM_NAME} MATCHES "Darwin" )
else()
  set ( Vector_source_list ${Vector_source_list} RotationXYZ.cc )
endif()

clhep_build_library ( Vector ${Vector_source_list} )
