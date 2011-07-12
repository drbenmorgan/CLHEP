# main Utility cmake instructions

# automake/autoconf variables
set( PACKAGE Utility )

set( Utility_CPPFLAGS "-I${includedir}" )
set( Utility_LDFLAGS  " " )
set( Utility_LIBS     " " )

configure_file ( ${CLHEP_SOURCE_DIR}/Utility/Utility-config.in
                 ${CLHEP_BINARY_DIR}/Utility/Utility-config @ONLY )
configure_file ( ${CLHEP_SOURCE_DIR}/Utility/Utility-deps.in
                 ${CLHEP_BINARY_DIR}/Utility/Utility-deps @ONLY )

install ( FILES ${CLHEP_BINARY_DIR}/Utility/Utility-config
          DESTINATION bin )

subdirs(Utility)
subdirs(test)
