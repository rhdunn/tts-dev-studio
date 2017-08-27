cmake_minimum_required(VERSION 3.1.0)
project(tts-dev-studio)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets Multimedia REQUIRED)

add_subdirectory(src)
