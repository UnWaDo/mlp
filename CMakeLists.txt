#
# Created by Anton Ivanov on 18.03.2023.
#

cmake_minimum_required(VERSION 3.20)
project(CPP7_MLP-1)

add_definitions("-Wall -Wextra -Werror -std=c++17")

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(src/s21_image)
add_subdirectory(src/s21_matrix)
add_subdirectory(src/s21_perceptron)
add_subdirectory(src/s21_batch_data)
