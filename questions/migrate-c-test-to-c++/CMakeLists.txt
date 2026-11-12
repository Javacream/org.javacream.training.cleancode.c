cmake_minimum_required(VERSION 3.16)
project(circle_test_migration LANGUAGES C CXX)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

add_library(circle STATIC src/circle.c)
target_include_directories(circle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
if(NOT MSVC)
    target_link_libraries(circle PUBLIC m)
endif()

add_executable(circle_c_test test/c/circle_test.c)
target_link_libraries(circle_c_test PRIVATE circle)
add_test(NAME circle_c COMMAND circle_c_test)

find_package(GTest QUIET)
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
    if(MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
    FetchContent_MakeAvailable(googletest)
endif()

add_executable(circle_cpp_test test/c++/circle_test.cpp)
target_link_libraries(circle_cpp_test PRIVATE circle GTest::gtest_main)
add_test(NAME circle_cpp COMMAND circle_cpp_test)
