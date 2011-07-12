# main Vector cmake instructions

# automake/autoconf variables
set( PACKAGE Vector )

clhep_package_config()

subdirs(Vector)
subdirs(src)
subdirs(test)
if ( build_docs )
  message(STATUS "building documents for ${PACKAGE}" )
  subdirs(doc)
endif()
