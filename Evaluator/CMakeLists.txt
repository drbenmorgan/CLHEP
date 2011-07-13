# main Evaluator cmake instructions

# automake/autoconf variables
set( PACKAGE Evaluator )

clhep_package_config()

add_subdirectory(Evaluator)
add_subdirectory(src)
add_subdirectory(test)
