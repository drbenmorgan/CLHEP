# main GenericFunctions cmake instructions

# automake/autoconf variables
set( PACKAGE GenericFunctions )

clhep_package_config()

subdirs(GenericFunctions)
subdirs(src)
subdirs(test)
if ( build_docs )
  message(STATUS "building documents for ${PACKAGE}" )
  subdirs(doc)
endif()
