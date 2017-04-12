#find_package(GTest REQUIRED)
find_package (Threads)
#include_directories(${GTEST_INCLUDE_DIR})

include(${CMAKE_SOURCE_DIR}/cmake/DownloadProject.cmake)

download_project(PROJ                googletest
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG             master
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

# When using CMake 2.8.11 or later, header path dependencies
# are automatically added to the gtest and gmock targets.
# For earlier CMake versions, we have to explicitly add the
# required directories to the header search path ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
            "${gmock_SOURCE_DIR}/include")
endif()

enable_testing()
add_custom_target(tests COMMENT "Builds all unit tests.")

function(mcl_add_test targetName targetFile)
    add_executable(${targetName} ${targetFile})
    target_link_libraries(${targetName} gtest gtest_main gmock gmock_main ${CMAKE_THREAD_LIBS_INIT})
    add_test(NAME ${targetName}
            WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
            COMMAND ${targetName})
    add_dependencies(tests ${targetName})
endfunction()

mcl_add_test(apitest APITest.cpp)