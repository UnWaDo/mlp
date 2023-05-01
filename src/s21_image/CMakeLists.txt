cmake_minimum_required(VERSION 3.2)
add_definitions("-Wall -Wextra -Werror -std=c++17")
set(CMAKE_CXX_STANDARD 17)
project(s21_image)

add_library(

        s21_image

        STATIC

        source/foundation/constructor.cc
        source/foundation/accessor.cc
        source/rescale.cc
        source/grayscale.cc
        source/write_file.cc
        source/matrix_conversion.cc
)

include_directories(include)
include_directories(test)
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

        s21_image_test

        test/main/main.cc

        test/foundation/accessor.cc
        test/foundation/constructor.cc

        test/rescale.cc
        test/grayscale.cc
        test/write_file.cc
        test/matrix_conversion.cc
)

include(GoogleTest)
target_link_libraries(

        s21_image_test

        s21_image
        s21_matrix
        GTest::gtest_main
)

gtest_discover_tests(
        s21_image_test
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test
)
