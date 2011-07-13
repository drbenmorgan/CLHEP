# main GenericFunctions cmake instructions

# automake/autoconf variables
set( PACKAGE GenericFunctions )

clhep_package_config()

add_subdirectory(GenericFunctions)
add_subdirectory(src)
add_subdirectory(test)
if ( build_docs )
  message(STATUS "building documents for ${PACKAGE}" )
  add_subdirectory(doc)
endif()
