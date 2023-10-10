####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/TempReceiver.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/TempReceiver.cpp"
)

# Uncomment and add any modules that this component depends on, else
# they might not be available when cmake tries to build this component.

# set(MOD_DEPS
#     Add your dependencies here
# )

register_fprime_module()

get_module_name("${CMAKE_CURRENT_LIST_DIR}")

if (CMAKE_TOOLCHAIN_FILE)
    find_library(MCP MCP9600 ${CMAKE_CURRENT_LIST_DIR}/../../libs/MCP9600/arm/)
else ()
    find_library(MCP MCP9600 ${CMAKE_CURRENT_LIST_DIR}/../../libs/MCP9600/x86)
endif ()

find_path(MCP9600_INCLUDES MCP9600.h ${CMAKE_CURRENT_LIST_DIR}/../../libs/MCP9600/src/)
include_directories(${MCP9600_INCLUDES})

target_link_libraries(
    ${MODULE_NAME}
    PUBLIC ${MCP}
   )
