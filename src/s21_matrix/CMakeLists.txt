#
# Created by Anton Ivanov on 18.03.2023.
#

cmake_minimum_required(VERSION 3.20)
project(s21_matrix)

add_definitions("-Wall -Wextra -Werror -std=c++17")

set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0135 NEW)

add_library(
        s21_matrix
        STATIC

        source/foundation/accessor.cc
        source/foundation/copy.cc
        source/foundation/description.cc
        source/foundation/matrix.cc
        source/foundation/operator.cc

        source/math.cc
        source/parse.cc
        source/transpose.cc
        source/transposed.cc
)

include_directories(include)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        test_s21_matrix
        test/main/main.cc

        test/foundation/accessor.cc
        test/foundation/description.cc
        test/foundation/matrix.cc
        test/foundation/operator.cc

        test/math.cc
        test/parse.cc
        test/transpose.cc
        test/transposed.cc
)

target_link_libraries(
        test_s21_matrix
        GTest::gtest_main

        s21_matrix
)

include(GoogleTest)
gtest_discover_tests(test_s21_matrix)
