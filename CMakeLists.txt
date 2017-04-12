cmake_minimum_required(VERSION 2.6)
project(MimicCommLib)

option(INCLUDE_TESTS "Choose whether to build tests in this run or not" OFF)

set(CMAKE_CXX_STANDARD 11)

find_package(MPI REQUIRED)
include_directories("${MPI_INCLUDE_PATH}")

add_subdirectory(src)

if(INCLUDE_TESTS)
    add_subdirectory(tests)
endif(INCLUDE_TESTS)