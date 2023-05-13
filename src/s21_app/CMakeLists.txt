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
include_directories(../dependencies/qcustomplot)

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

        source/s21_main_window.cc
        ui/main_window.ui
        include/s21_main_window.h

        source/s21_new_perceptron.cc
        ui/new_perceptron.ui
        include/s21_new_perceptron.h

        source/s21_main_model.cc
        include/s21_main_model.h

        source/s21_main_controller.cc
        include/s21_main_controller.h

        source/s21_progress_window.cc
        ui/progress_window.ui

        source/s21_training_history.cc
        include/s21_training_history.h

        source/s21_draw_image.cc
        include/s21_draw_image.h
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
        qcustomplot
)
