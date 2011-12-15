# main Exceptions cmake instructions

# automake/autoconf variables
set( PACKAGE Exceptions )

# define dependency list that will be used in several places
list(APPEND ${PACKAGE}_DEPS Cast RefCount )
clhep_package_config()

add_subdirectory(Exceptions)
add_subdirectory(src)
add_subdirectory(test)
if ( CLHEP_BUILD_DOCS )
  message(STATUS "building documents for ${PACKAGE}" )
  add_subdirectory(doc)
endif()
