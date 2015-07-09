#-------------------------------------------------------------
#  building CLHEP with cmake
#-------------------------------------------------------------

At this time, the cmake build system only supports building 
CLHEP as a complete package, starting from the top level directory.

This package requires cmake 2.6 or later.

#-------------------------------------------------------------
#  installing from a source code tar ball
#-------------------------------------------------------------

Unwind the source code tar ball in some relevant directory.
Determine where the files will be installed.
Create a build directory that is NOT in the source code directory tree.
Make sure cmake is in your path.

cd <build_directory>

cmake -DCMAKE_INSTALL_PREFIX=<install_dir> <source_code_dir>
   (Note that files will be installed under /usr/local if you do not 
    specify a prefix.)
make
   (Build temporary copies of libraries and executables.)
make test
   (Run the tests.)
make install
   (Copy libraries, headers, executables, etc. to relevant 
    subdirectories under <install_dir>.)

#-------------------------------------------------------------
#  cmake options
#-------------------------------------------------------------

-DCMAKE_INSTALL_PREFIX=/install/path
-DCMAKE_BUILD_TYPE=Debug|Release|RelWithDebInfo|MinSizeRel
-DCLHEP_BUILD_DOCS=ON

-DCMAKE_C_COMPILER=...
-DCMAKE_CXX_COMPILER=...
-DCMAKE_CXX_FLAGS="list_of_flags"

-DCLHEP_BUILD_CXXSTD=ON (enable c++11 extensions and thread support)
-DCLHEP_BUILD_CXXSTD="-std=c++NN" (use specified c++ extension and thread support)

-DLIB_SUFFIX=64 (installs the libraries in a lib64 subdirectory)

IMPORTANT:
If you include -DCLHEP_BUILD_DOCS=ON, do not use "make -jN"

#-------------------------------------------------------------
# building documents
#-------------------------------------------------------------

Documents are not built or installed automatically.  
If you wish to build and install the documents, 
add -DCLHEP_BUILD_DOCS=ON to your cmake command.   
Documents will then be built during the normal build.
You will need to have latex in your path.

#-------------------------------------------------------------
# building from git
#-------------------------------------------------------------

To work with the head:
git clone http://git.cern.ch/pub/CLHEP

To work with a tag:
git clone http://git.cern.ch/pub/CLHEP
Use "git tag" to see the available tags.
git co <tag>

Now continue with directions as if you unpacked a source code tarball.

#-------------------------------------------------------------
# building cmake
#-------------------------------------------------------------

cmake 2.6 or later is readily available for Linux,
although you may need to install it

download the cmake tar file from http://www.cmake.org/cmake/resources/software.html
You may find a usable binary distribution there.  
If not, get the source code and proceed as below (for either MacOSX or Linux).

Unwind the source code tarball.  This directory is <cmake_source_dir>.
Identify a separate build directory and a separate install directory: 
<cmake_build_dir> and <cmake_install_dir>.

cd <cmake_build_dir>
<cmake_source_dir>/bootstrap --prefix=<cmake_install_dir>
make
make install

Add <cmake_install_dir>/bin to your path.

#-------------------------------------------------------------
