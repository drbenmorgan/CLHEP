# parse a version string and set the cmake project subversions
#
# parse_version( package version )

macro( parse_version package vers )

  # CLHEP versions have 4 numbers
  STRING( REGEX REPLACE "^([0-9]+)\\.[0-9]+\\.[0-9]+\\.[0-9]+.*" "\\1" ${package}_Major "${vers}" )
  STRING( REGEX REPLACE "^[0-9]+\\.([0-9]+)\\.[0-9]+\\.[0-9]+.*" "\\1" ${package}_SubMajor "${vers}" )
  STRING( REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+)\\.[0-9]+.*" "\\1" ${package}_Minor "${vers}" )
  STRING( REGEX REPLACE "^[0-9]+\\.[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" ${package}_SubMinor "${vers}" )
  ##message(STATUS "version ${vers} parses to ${${package}_Major} ${${package}_SubMajor} ${${package}_Minor} ${${package}_SubMinor}" )

endmacro( parse_version )
