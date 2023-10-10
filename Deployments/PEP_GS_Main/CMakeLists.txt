####
# 'PEP_GS_Main' Deployment:
#
# This sets up the build for the 'PEP_GS_Main' Application, including custom
# components. In addition, it imports FPrime.cmake, which includes the core F Prime components.
#
#####

###
# Basic Project Setup
###
cmake_minimum_required(VERSION 3.13)
cmake_policy(SET CMP0048 NEW)
project(PEP_GS_Main VERSION 1.0.0 LANGUAGES C CXX)

###
# F' Core Setup
# This includes all of the F prime core components, and imports the make-system.
###
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime.cmake")
# NOTE: register custom targets between these two lines
include("${FPRIME_FRAMEWORK_PATH}/cmake/FPrime-Code.cmake")

###
# Components and Topology
###
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Top/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Components/TempSender/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Components/TempReceiver/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Datatypes/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Ports/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/libs/MCP9600/")

#User Added
#add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/libs/")

set(SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/Main.cpp")
set(MOD_DEPS ${PROJECT_NAME}/Top)

#User Added
#Might need this?
#set(MOD_DEPS ${CMAKE_CURRENT_LIST_DIR}/libs)
#get_module_name("${CMAKE_CURRENT_LIST_DIR}")
#find_library(MCP MCP9600 "${CMAKE_CURRENT_LIST_DIR}/libs/MCP9600/build/")
#find_path(MCP9600_INCLUDES MCP9600.h "${CMAKE_CURRENT_LIST_DIR}/libs/MCP9600/src/")
#include_directories("${MCP9600_INCLUDES}")

#target_link_libraries(
#    ${MODULE_NAME}
#    PUBLIC ${MCP}
#    )

register_fprime_deployment()
