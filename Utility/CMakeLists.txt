# main Utility cmake instructions

# automake/autoconf variables
set( PACKAGE Utility )

clhep_package_config_no_lib()

add_subdirectory(Utility)
add_subdirectory(test)
