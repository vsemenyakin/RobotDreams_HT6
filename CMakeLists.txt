cmake_minimum_required(VERSION 3.20)

project(ballistics CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ballistics_executable src/main.cpp)
target_include_directories(ballistics_executable PUBLIC include)

add_library(ballistics STATIC
	src/ballistics.cpp
	include/ballistics.hpp)
target_include_directories(ballistics PUBLIC include)

target_link_libraries(ballistics_executable PRIVATE ballistics)

# ================= Tests =================

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(ballistics_tests
    tests/ballistics_tests.cpp
)
target_link_libraries(ballistics_tests
    PRIVATE
        ballistics
        GTest::gtest_main
)

target_compile_definitions(ballistics_tests PRIVATE TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")

enable_testing()
include(GoogleTest)
gtest_discover_tests(ballistics_tests)