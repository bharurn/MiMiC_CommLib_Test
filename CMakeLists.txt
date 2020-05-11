cmake_minimum_required(VERSION 3.12)
project(MiMiCCommmLib
        VERSION 0.2.0
        DESCRIPTION "Communication library for the MiMiC multiscale simulation framework"
        HOMEPAGE_URL "https://gitlab.com/MiMiC-projects/CommLib"
        LANGUAGES CXX)

option(INCLUDE_TESTS "Choose whether to build tests in this run or not" OFF)
option(CODE_COVERAGE "Enable code coverage report" OFF)
option(DOWNLOAD_GTEST "Whether to download GTest library" ON)
option(BUILD_FORTRAN_API "Whether to build Fortran API module or not" OFF)

if(BUILD_FORTRAN_API)
    enable_language(Fortran)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if(CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -traceback -fpic")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fpic")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Og -pedantic -Wall -fPIC")
    if(CODE_COVERAGE)
        set(CMAKE_CXX_FLAGS
                "${CMAKE_CXX_FLAGS} --coverage")
    endif()
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -fPIC")
else()
    message(WARNING "Only Intel and GCC compiler flags have been configured")
endif()

find_package(MPI REQUIRED)
include_directories("${MPI_CXX_INCLUDE_PATH}")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(COMMLIB_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/src/transport ${CMAKE_CURRENT_SOURCE_DIR}/src/serializer ${CMAKE_CURRENT_SOURCE_DIR}/src/message)
include_directories(${COMMLIB_DIRS})
add_subdirectory(src)

if(INCLUDE_TESTS)
    include(CTest)
    configure_file(${CMAKE_SOURCE_DIR}/cmake/CTestCustom.cmake
            ${CMAKE_BINARY_DIR}/CTestCustom.cmake
            @ONLY)
    set(CTEST_OUTPUT_ON_FAILURE ON)
    add_subdirectory(tests)
endif(INCLUDE_TESTS)
