# main RandomObjects cmake instructions

# automake/autoconf variables
set( PACKAGE RandomObjects )

# define dependency list that will be used in several places
list(APPEND ${PACKAGE}_DEPS Random Matrix Vector )
clhep_package_config()

subdirs(RandomObjects)
subdirs(src)
subdirs(test)
