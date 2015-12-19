# parse a version string and set the cmake project subversions
#
# parse_version( package version )

macro(parse_version package vers)
  # CLHEP versions have 4 numbers
  string(REGEX REPLACE
    "^([0-9]+)\\.[0-9]+\\.[0-9]+\\.[0-9]+.*"
    "\\1"
    ${package}_Major
    "${vers}"
    )
  string(REGEX REPLACE
    "^[0-9]+\\.([0-9]+)\\.[0-9]+\\.[0-9]+.*"
    "\\1"
    ${package}_SubMajor
    "${vers}"
    )
  string(REGEX REPLACE
    "^[0-9]+\\.[0-9]+\\.([0-9]+)\\.[0-9]+.*"
    "\\1"
    ${package}_Minor
    "${vers}"
    )
  string(REGEX REPLACE
    "^[0-9]+\\.[0-9]+\\.[0-9]+\\.([0-9]+).*"
    "\\1"
    ${package}_SubMinor
    "${vers}"
    )
endmacro()
