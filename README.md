CLHEP C++ Class Library for High Energy Physics
===============================================

- [CLHEP Home Page](http://proj-clhep.web.cern.ch/proj-clhep/)
- [Git Repository] (http://git.cern.ch/pubweb/CLHEP.git)
- [Bug Reports and Feature Requests](https://its.cern.ch/jira/browse/CLHEP/)

Installing CLHEP
================
Prerequisites
-------------
- Linux/OS X/BSD/Windows OS
- C++11 compliant compiler (GCC >= 4.8, Clang >= 3.3, Intel >= 15, MSVC >= 19)
  - If the Intel compiler is used with GCC compatibility, it should be configured
    to use GCC 4.8 or higher
- [CMake](http://www.cmake.org) >= 3.2

Building CLHEP with CMake
-------------------------
At this time, the cmake build system only supports building CLHEP as a 
complete package, starting from the top level directory.

Unwind the source code tar ball in some relevant directory. Determine a prefix
under which CLHEP should be installed. Create a build directory that is 
NOT in the source code directory tree (i.e. the tree rooted where this README
resides).

```
$ cd <build_directory>
$ cmake -DCMAKE_INSTALL_PREFIX=<install_dir> <source_code_dir>
$ cmake --build . --config RelWithDebInfo
$ ctest
$ cmake --build . --target install
```

The above will configure the build, compile CLHEP libraries with optimization and
debugging symbols, run the test suite and finally install the CLHEP binaries and
headers under the chosen install prefix.

Additional CMake Options
------------------------
The following arguments may be passed to CMake at the configuration stage either
via the command line or the `cmake-gui` and `ccmake` interfaces.

- `-DCMAKE_INSTALL_PREFIX=/install/path`
  - Change prefix under which to install CLHEP
  - Defaults to `/usr/local` on UNIX platforms
- `-DCLHEP_BUILD_CXXSTD=-std=c++NM`
  - Compile CLHEP against C++ Standard `NM`
  - Defaults to `11`
  - `NM` can be chosen from `11`, `1y` or `14`.
- `-DLIB_SUFFIX=64`
  - installs the libraries in a `lib64` subdirectory
- `-DCLHEP_BUILD_DOCS=ON`
  - Build and install CLHEP documentation
  - Requires [Doxygen](http://www.doxygen.org) and a LaTeX compiler

The compiler discovered and used by CMake to build CLHEP may be
selected either by setting the `CC` and `CXX` shell/environment variables
to point to the required compilers, or by the CMake variables 
`CMAKE_C_COMPILER` and `CMAKE_CXX_COMPILER`. Note that you *should not*
change the discovered compiler after initial configuration. If you
require concurrent builds against different compilers, use separate
build directories for each compiler.

Building CLHEP from Git
-----------------------
To work with the head:

```
$ git clone http://git.cern.ch/pub/CLHEP
```

To work with a tag:

```
$ git clone http://git.cern.ch/pub/CLHEP
... Use "git tag" to see the available tags.
$ git co <tag>
```

Now continue with directions as if you unpacked a source code tarball.


Building Projects using CLHEP
=============================
Using CMake
-----------
If your project uses CMake as its buildtool, CLHEP installs a CMake 
"Package Config" file that can be used by CMake's `find_package` command.
When found, this file will set up CMake imported targets for the CLHEP
libraries which may then be linked to. For example, to create an
executable that uses CLHEP headers and libraries, your CMake script
would do

```cmake
...
find_package(CLHEP REQUIRED)

add_executable(MyProgram MyProgram.cc)
target_link_libraries(MyProgram CLHEP::CLHEP)
```

Here `CLHEP::CLHEP` is the imported target for the full CLHEP shared library.
CMake will handle setting up header and library paths for you. Imported targets
also exist for the component libraries:

```cmake
...
target_link_libraries(MyProgram CLHEP::Vector CLHEP::Random)
```

If you installed CLHEP to a non-standard location, you may need to
add this location to the `CMAKE_PREFIX_PATH`. This may be done either by
passing `CMAKE_PREFIX_PATH` with the location as a command line argument 
to `cmake` or by setting `CMAKE_PREFIX_PATH` in the environment (as a PATH style variable).

Using `pkg-config`
------------------
If your project uses `pkg-config` to locate build dependencies, CLHEP installs
`.pc` files for both the full and component CLHEP libraries. The standard
`pkg-config` commands may be used to discover required compiler and liker 
flags, for example

```
$ pkg-config --cflags --libs clhep
```

or for component libraries

```
$ pkg-config --cflags --libs clhep-vector clhep-random
```

If you installed CLHEP to a non-standard location, you may need to add the
directory holding the `.pc` files (`<CMAKE_INSTALL_PREFIX>/lib<LIB_SUFFIX>/pkgconfig`)
to the `PKG_CONFIG_PATH` environment variable.

