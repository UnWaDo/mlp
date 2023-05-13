cmake_minimum_required(VERSION 3.2)
project(s21_batch_data)

add_definitions("-Wall -Wextra -Werror -std=c++17")

set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0135 NEW)

add_library(

        s21_batch_data

        STATIC

        source/foundation/accessor.cc
        source/foundation/constructor.cc
        source/foundation/operator.cc
        source/loading.cc
        source/validate.cc
        source/train.cc
        source/shuffle.cc
)

include_directories(include)
include_directories(test)
include_directories(../s21_matrix/include)
include_directories(../s21_perceptron/include)

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
        s21_batch_data_test

        test/foundation/accessor.cc
        test/foundation/constructor.cc
        test/foundation/operator.cc
        test/loading.cc
        test/validate.cc
        test/train.cc
        test/shuffle.cc
)

include(GoogleTest)
target_link_libraries(

        s21_batch_data_test

        s21_batch_data
        s21_perceptron
        s21_matrix
        GTest::gtest_main
)

gtest_discover_tests(
        s21_batch_data_test
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test
)
