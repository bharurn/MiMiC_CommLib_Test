cmake_minimum_required(VERSION 2.6)
project(MimicCommLib)

option(INCLUDE_TESTS "Choose whether to build tests in this run or not" OFF)
option(CODE_COVERAGE "Enable code coverage report" OFF)
option(DOWNLOAD_GTEST "Whether to download GTest library" ON)

set(CMAKE_CXX_STANDARD 11)

if(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -traceback -check all -debug all -warn all")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -Og -pedantic -Wall")
    if(CODE_COVERAGE)
        set(CMAKE_CXX_FLAGS
                "${CMAKE_CXX_FLAGS} --coverage")
    endif()
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
else()
    message(WARNING "Only Intel and GCC compiler flags have been configured")
endif()


find_package(MPI REQUIRED)
include_directories("${MPI_INCLUDE_PATH}")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_subdirectory(src)

if(INCLUDE_TESTS)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
    include(CTest)
    configure_file(${CMAKE_SOURCE_DIR}/cmake/CTestCustom.cmake
            ${CMAKE_BINARY_DIR}/CTestCustom.cmake
            @ONLY)
    set(CTEST_OUTPUT_ON_FAILURE ON)
    add_subdirectory(tests)
endif(INCLUDE_TESTS)