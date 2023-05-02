#
# Created by Anton Ivanov on 18.03.2023.
#

cmake_minimum_required(VERSION 3.20)
project(s21_perceptron)

add_definitions("-Wall -Wextra -Werror -std=c++17")

set(CMAKE_CXX_STANDARD 17)

add_library(
        s21_perceptron
        STATIC

        source/graph_perceptron/foundation/graph_perceptron.cc

        source/graph_perceptron/back_propagation.cc
        source/graph_perceptron/export_perceptron_to_file.cc
        source/graph_perceptron/forward_propagation.cc

#        source/foundation/accessor.cc
#        source/foundation/copy.cc
#        source/foundation/description.cc
        source/matrix_perceptron/foundation/matrix_perceptron.cc
#        source/foundation/operator.cc

        source/matrix_perceptron/back_propagation.cc
        source/matrix_perceptron/export_perceptron_to_file.cc
        source/matrix_perceptron/forward_propagation.cc

        source/utils/relu.cc
        source/utils/sigmoid.cc
        source/utils/softmax.cc
)

include_directories(include)
include_directories(../s21_matrix/include)

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
        test_s21_matrix_perceptron
        test/main/main.cc

        test/matrix_perceptron/back_propagation.cc
        test/matrix_perceptron/export_perceptron_to_file.cc
        test/matrix_perceptron/forward_propagation.cc
)

target_link_libraries(
        test_s21_matrix_perceptron
        GTest::gtest_main

        s21_perceptron
        s21_matrix
)

add_executable(
        test_s21_utils
        test/main/main.cc

        test/utils/relu.cc
        test/utils/sigmoid.cc
        test/utils/softmax.cc
)

target_link_libraries(
        test_s21_utils
        GTest::gtest_main

        s21_perceptron
        s21_matrix
)

add_executable(
        test_s21_graph_perceptron
        test/main/main.cc

        test/graph_perceptron/back_propagation.cc
        test/graph_perceptron/export_perceptron_to_file.cc
        test/graph_perceptron/forward_propagation.cc
)

target_link_libraries(
        test_s21_graph_perceptron
        GTest::gtest_main

        s21_perceptron
        s21_matrix
)

include(GoogleTest)
gtest_discover_tests(test_s21_utils)
gtest_discover_tests(test_s21_matrix_perceptron)
gtest_discover_tests(test_s21_graph_perceptron)

file(COPY test/resource DESTINATION .)
