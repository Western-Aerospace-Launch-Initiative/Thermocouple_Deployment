cmake_minimum_required(VERSION 3.13)

project(MCP9600_Tests)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
#FetchContent_MakeAvailable(googletest)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()
enable_testing()

add_executable(
  MCP9600_Tests
  TestMain.cpp
)
target_link_libraries(
    #MCP9600
    MCP9600_Tests
    GTest::gtest_main
    MCP9600
)

include(GoogleTest)
gtest_discover_tests(MCP9600_Tests)

#Autorun UT
#add_custom_command(
#        TARGET MCP9600_Tests
#        POST_BUILD
#        COMMENT "Running Unit Tests..."
#        COMMAND ./MCP9600_Tests
#        )

