
set( Random_tests  testRandom
                   testRandDists )
if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
set( Random_simple_tests testSaveEngineStatus 
			 testInstanceRestore 
			 testSaveSharedEngines
			 testStaticStreamSave 
			 testAnonymousEngineRestore 
			 testVectorSave
			 testBug73093 
			 testEngineCopy 
			 testDistCopy 
			 testRanecuSequence )
else()
set( Random_simple_tests testSaveEngineStatus 
			 testInstanceRestore 
			 testSaveSharedEngines
			 testStaticStreamSave 
			 testAnonymousEngineRestore 
			 testVectorSave
			 testBug58950 
			 testBug73093 
			 testEngineCopy 
			 testDistCopy 
			 testRanecuSequence )
endif()

foreach ( test ${Random_tests} )
  clhep_test( ${test} )
endforeach ( test ${Random_tests} )

foreach ( test ${Random_simple_tests} )
  clhep_test( ${test} SIMPLE )
endforeach ( test ${Random_simple_tests} )
