#
# Created by Anton Ivanov on 09.04.2023.
#

cmake_minimum_required(VERSION 3.2)
add_definitions("-Wall -Wextra -Werror -std=c++17")
set(CMAKE_CXX_STANDARD 17)
project(CPP7_MLP)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

enable_testing()

# add_subdirectory(src/s21_graph)
# add_subdirectory(src/s21_graph_algorithms)
add_subdirectory(src/s21_matrix)
# add_subdirectory(src/s21_navigator)
# add_subdirectory(src/s21_queue)
# add_subdirectory(src/s21_stack)
add_subdirectory(src/s21_image)
