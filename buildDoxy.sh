#! /bin/sh

# this script runs doxygen to create the html reference manual
# For a number of reasons, doxygen needs to run in the top directory 
# of the CLHEP source code distribution.
# Copy or move the generated html directory to the appropriate place.

set -x
# run doxygen if present
if [ `whereis doxygen | wc -w` -gt 1 ]; then
   rm -rf html
   doxygen doxygen.conf
fi
