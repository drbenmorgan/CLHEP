# main Random cmake instructions

# automake/autoconf variables
set( PACKAGE Random )

clhep_package_config()

subdirs(Random)
subdirs(src)
subdirs(test)
if ( build_docs )
  message(STATUS "building documents for ${PACKAGE}" )
  subdirs(doc)
endif()
