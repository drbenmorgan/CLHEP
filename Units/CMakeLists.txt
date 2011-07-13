# main Units cmake instructions

# automake/autoconf variables
set( PACKAGE Units )

set( Units_CPPFLAGS "-I${includedir}" )
set( Units_LDFLAGS  " " )
set( Units_LIBS     " " )

configure_file ( ${CLHEP_SOURCE_DIR}/Units/Units-config.in
                 ${CLHEP_BINARY_DIR}/Units/Units-config @ONLY )

install ( FILES ${CLHEP_BINARY_DIR}/Units/Units-config
          DESTINATION bin )

add_subdirectory(Units)
add_subdirectory(test)
if ( build_docs )
  message(STATUS "building documents for ${PACKAGE}" )
  add_subdirectory(doc)
endif()
