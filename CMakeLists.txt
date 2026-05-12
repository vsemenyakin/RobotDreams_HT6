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
