####
# BeagleBone Toolchain
#
# This is a toolchain for the BeagleBone. This toolchain can be used ot build
# against the BeagleBone embedded Linux target. In order to use this toolchain,
# the BeagleBone cross-compiler should be installed on a Linux host. These
# tools are installable as follows:
#   sudo apt install gcc-arm-linux-gnueabihf g++-arm-linux-gnueabihf
####

# Set the system information
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Set the GNU ARM toolchain
set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")

#set(CMAKE_FIND_ROOT_PATH  "/usr/bin")

# DO NOT EDIT: F prime searches the host for programs, not the cross
# compile toolchain
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# DO NOT EDIT: F prime searches for libs, includes, and packages in the
# toolchain when cross-compiling.
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
