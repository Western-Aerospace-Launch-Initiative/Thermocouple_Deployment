cmake_minimum_required(VERSION 3.13)

project(MCP9600)

add_library(MCP9600 MCP9600.c)

if (CMAKE_TOOLCHAIN_FILE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR/../armlibs}"
        )
else ()
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR/../x86libs}"
        )
endif()

#add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test/ut)

add_compile_options(-Wall -Wextra -Wpedantic)
