# main Vector cmake instructions

# automake/autoconf variables
set( PACKAGE Vector )

clhep_package_config()

add_subdirectory(Vector)
add_subdirectory(src)
add_subdirectory(test)
if ( CLHEP_BUILD_DOCS )
  message(STATUS "building documents for ${PACKAGE}" )
  add_subdirectory(doc)
endif()
