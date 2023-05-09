#
# Created by Anton Ivanov on 06.05.2023.
#

cmake_minimum_required(VERSION 3.20)
project(s21_app)

add_definitions("-Wall -Wextra -Werror -std=c++17")

set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0135 NEW)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui/)

include_directories(include)
include_directories(../s21_batch_data/include)
include_directories(../s21_image/include)
include_directories(../s21_matrix/include)
include_directories(../s21_perceptron/include)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Multimedia
        REQUIRED)

add_executable(

        s21_app

        source/main/main.cc
)

add_library(
        s21_windows

        source/s21_windows.cc
        ui/main_window.ui
        include/s21_windows.h

        source/s21_edit_perceptron.cc
        ui/edit_perceptron.ui
)

target_link_libraries(

        s21_windows

        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Multimedia

        s21_batch_data
        s21_image
        s21_perceptron
        s21_matrix
)

target_link_libraries(

        s21_app

        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Multimedia

        s21_windows
        s21_batch_data
        s21_image
        s21_perceptron
        s21_matrix
)
