# main Geometry cmake instructions

# automake/autoconf variables
set( PACKAGE Geometry )

# define dependency list that will be used in several places
list(APPEND ${PACKAGE}_DEPS Vector )
clhep_package_config()

subdirs(Geometry)
subdirs(src)
subdirs(test)
