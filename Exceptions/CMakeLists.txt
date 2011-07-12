# main Exceptions cmake instructions

# automake/autoconf variables
set( PACKAGE Exceptions )

# define dependency list that will be used in several places
list(APPEND ${PACKAGE}_DEPS Cast RefCount )
clhep_package_config()

subdirs(Exceptions)
subdirs(src)
subdirs(test)
if ( build_docs )
  message(STATUS "building documents for ${PACKAGE}" )
  subdirs(doc)
endif()
