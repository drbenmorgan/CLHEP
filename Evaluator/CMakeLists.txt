# main Evaluator cmake instructions

# automake/autoconf variables
set( PACKAGE Evaluator )

clhep_package_config()

subdirs(Evaluator)
subdirs(src)
subdirs(test)
