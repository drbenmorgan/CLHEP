# main Units cmake instructions

# automake/autoconf variables
set( PACKAGE Units )

clhep_package_config_no_lib()

add_subdirectory(Units)
add_subdirectory(test)
if ( CLHEP_BUILD_DOCS )
  message(STATUS "building documents for ${PACKAGE}" )
  add_subdirectory(doc)
endif()
