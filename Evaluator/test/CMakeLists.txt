
clhep_test( testEvaluator )
clhep_test( testBug66214 SIMPLE )

if( NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
clhep_test( testBug90848 SIMPLE )
endif()

