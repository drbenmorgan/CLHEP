# main GenericFunctions cmake instructions

# automake/autoconf variables
set( PACKAGE GenericFunctions )

clhep_package_config()

# check to see if gsl is available
set( GSL_DIR $ENV{GSL} )
if( GSL_DIR )
  message( STATUS "found gsl at ${GSL_DIR}")
  include_directories ( ${GSL_DIR}/include )
endif()

add_subdirectory(GenericFunctions)
add_subdirectory(src)
add_subdirectory(test)
if ( CLHEP_BUILD_DOCS )
  message(STATUS "building documents for ${PACKAGE}" )
  add_subdirectory(doc)
endif()
