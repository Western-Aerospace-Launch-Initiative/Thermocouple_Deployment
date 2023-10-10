#!/bin/bash

# Author: Noah Braasch
# Date: 5/15/2023
# Revision: 000
# Revisor: 
#********************* 

install_compiler() {
    sudo apt install -y gcc-arm-linux-gnueabihf && g++-arm-linux-gnueabihf
}

finish_build() {
    fprime-util generate beaglebone
    fprime-util build beaglebone
}

install_compiler
git clone git@github.com:Western-Aerospace-Launch-Initiative/Provisioning-Scripts.git
mv Provisioning-Scripts/beablebone.toolchain ../../fprime/cmake/toolchain
rm -r -f Provisioning-Scripts
fprime-util purge beaglebone -f
finish_build
