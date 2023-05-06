#
# Created by Anton Ivanov on 06.05.2023.
#

cmake_minimum_required(VERSION 3.20)
project(s21_app)

add_definitions("-Wall -Wextra -Werror -std=c++17")

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(

        s21_app

        source/main/main.cc
)

target_link_libraries(

        s21_app

        Qt6::Core
        Qt6::Gui
        Qt6::Widgets

        s21_batch_data
        s21_image
        s21_matrix
        s21_perceptron
)


include_directories(include)

include_directories(../s21_batch_data/include)
include_directories(../s21_image/include)
include_directories(../s21_matrix/include)
include_directories(../s21_perceptrom/include)
