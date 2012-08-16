#----------------------------------------------------------------------------
# Finally, we can configure the toolchain files for build and install
# directories.
#
# Toolchains:
#  - CMake via use of 'CLHEPConfig.cmake'
#  - pkgconfig via 'clhep.pc'
#
# We only do this for the main CLHEP library to illustrate the basic
# pattern. It can be extended to handle the component packages, but this
# is more complex and would hide the basic concepts. 
#
# Both are fully relocatable, like clhep-config, so can be distributed in
# relocatable binary packages.

# code supplied by Ben Morgan Ben.Morgan@warwick.ac.uk

macro(clhep_toolchain)

#----------------------------------------------------------------------------
# - First we handle the build tree
# This setup allows a build of CLHEP to be used directly *without* installing
# it. This allows several useful development patterns, such as checking an
# application using CLHEP works with different versions/tag sets.
#
# First we set the needed variables
set(CLHEP_VERSION ${VERSION})
set(CLHEP_DEFINITIONS )
set(CLHEP_INCLUDE_DIR ${PROJECT_BINARY_DIR})

# Now we configure the CLHEPConfig and CLHEPConfigVersion file templates,
# outputting to the top level of the build tree.
# This allows users to 'point' CMake to the build by something like
#  
#  # Some CMakeLists.txt
#  ...
#  find_package(CLHEP 2.1.0.1 REQUIRED)
#
# in their buildscript, and then pointing cmake to the build directory via
#
#  cmake -DCLHEP_DIR=/path/to/clhep/build  /path/to/source/of/app
#
configure_file(${PROJECT_SOURCE_DIR}/cmake/Templates/CLHEPConfigVersion.cmake.in
  ${PROJECT_BINARY_DIR}/CLHEPConfigVersion.cmake 
  @ONLY
  )

configure_file(${PROJECT_SOURCE_DIR}/cmake/Templates/CLHEPConfig.cmake.in
  ${PROJECT_BINARY_DIR}/CLHEPConfig.cmake 
  @ONLY
  )

# We 'export' the main CLHEP library targets from the build tree.
# This file is include()d by CLHEPConfig.cmake
export(TARGETS CLHEP CLHEPS 
  FILE ${PROJECT_BINARY_DIR}/CLHEPLibraryDepends.cmake
  )


# Now we configure clhep.pc.
# In the build tree we hardcode all paths, as we never need to relocate
# a build tree
#
set(CLHEP_PKGCONFIG_PREFIX ${PROJECT_BINARY_DIR})
set(CLHEP_PKGCONFIG_INCLUDEDIR ${CLHEP_INCLUDE_DIR})
set(CLHEP_PKGCONFIG_LIBDIR ${PROJECT_BINARY_DIR}/lib${LIB_SUFFIX})

configure_file(${PROJECT_SOURCE_DIR}/cmake/Templates/clhep.pc.in
  ${PROJECT_BINARY_DIR}/clhep.pc
  @ONLY
  )


#----------------------------------------------------------------------------
# - Now we handle the installation tree
#
# Again we set the needed variable first. Not all have actually changed,
# but we set again for clarity and just to be sure.
set(CLHEP_VERSION ${VERSION})
set(CLHEP_DEFINITIONS )

# The setup of the include dir is slightly different because we want
# to make the install relocatable (Current CLHEP setup *is* relocatable).
# We use a relative path from the directory where the CLHEPConfig.cmake
# file is installed to the actual include dir. 
file(RELATIVE_PATH _relincpath 
  ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/CLHEP-${VERSION}
  ${CMAKE_INSTALL_PREFIX}/include
  )
set(CLHEP_INCLUDE_DIR "\${_thisdir}/${_relincpath}")

# Now we configure the CLHEPConfig and CLHEPConfigVersion file templates,
# outputting to a directory in the build directory. This is simply a
# placeholder to store them until we install later.  
configure_file(${PROJECT_SOURCE_DIR}/cmake/Templates/CLHEPConfigVersion.cmake.in
  ${PROJECT_BINARY_DIR}/InstallTreeFiles/CLHEPConfigVersion.cmake 
  @ONLY
  )

configure_file(${PROJECT_SOURCE_DIR}/cmake/Templates/CLHEPConfig.cmake.in
  ${PROJECT_BINARY_DIR}/InstallTreeFiles/CLHEPConfig.cmake 
  @ONLY
  )

# Also configure the pkgconfig file, again outputting to a directory under
# the build directory ready for installation
# Now we use the 'pcfiledir' variable of pkg-config - this tells us the
# directory where clhep.pc is located. Since we know we'll install clhep.pc
# in CMAKE_INSTALL_PREFIX/lib/pkgconfig, we can calculate relative paths
# to the include and lib dirs.... This make the pc file fully relocatable!!
# If you later use GNUInstallDirs.cmake, this would need more work to
# ensure accurate calculation of the relative path.
set(CLHEP_PKGCONFIG_PREFIX "\${pcfiledir}/../..")
set(CLHEP_PKGCONFIG_LIBDIR "\${prefix}/lib${LIB_SUFFIX}")
set(CLHEP_PKGCONFIG_INCLUDEDIR "\${prefix}/include")

configure_file(${PROJECT_SOURCE_DIR}/cmake/Templates/clhep.pc.in
  ${PROJECT_BINARY_DIR}/InstallTreeFiles/clhep.pc
  @ONLY
  )

# - Install the config files, and 'install export' the library depends file
#   The choice of 'lib/CLHEP-<VERSION>' is based on the recommendations
#   in the CMake documentation for find_package on UNIX so that 
#   CMake can potentially find the Config file automatically. We don't
#   consider the Apple case because we don't (yet) build CLHEP as a Framework.
#   The Windows case can be easily added later.
#   The location can of course be modified if you wish.
install(FILES
  ${PROJECT_BINARY_DIR}/InstallTreeFiles/CLHEPConfigVersion.cmake 
  ${PROJECT_BINARY_DIR}/InstallTreeFiles/CLHEPConfig.cmake 
  DESTINATION lib${LIB_SUFFIX}/CLHEP-${VERSION}
  )

install(EXPORT CLHEPLibraryDepends DESTINATION lib${LIB_SUFFIX}/CLHEP-${VERSION})

# Install the pkg-config file. The choice of 'lib${LIB_SUFFIX}/pkgconfig' for the 
# installation seems fairly standard.
install(FILES
  ${PROJECT_BINARY_DIR}/InstallTreeFiles/clhep.pc
  DESTINATION lib${LIB_SUFFIX}/pkgconfig
  )

# - And we should be done...

endmacro(clhep_toolchain)
