# main Matrix cmake instructions

# automake/autoconf variables
set( PACKAGE Matrix )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDISABLE_ALLOC")

# define dependency list that will be used in several places
list(APPEND ${PACKAGE}_DEPS Random Vector )
clhep_package_config()

add_subdirectory(Matrix)
add_subdirectory(src)
add_subdirectory(test)
