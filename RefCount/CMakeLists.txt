# main RefCount cmake instructions

# automake/autoconf variables
set( PACKAGE RefCount )

clhep_package_config()

add_subdirectory(RefCount)
add_subdirectory(src)
