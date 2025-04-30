cmake_minimum_required(VERSION 3.26)
project(
        labwork8-Alice583
        VERSION 1.0
        DESCRIPTION "C++ Year 2023 labwork8"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

add_executable(main bin/main.cpp
lib/BinarySearchTree.h
lib/BinarySearchTree.cpp)

add_executable(tests
        ../tests/tests.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
target_link_libraries(
        tests
        GTest::gtest_main
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/tests)

include(GoogleTest)