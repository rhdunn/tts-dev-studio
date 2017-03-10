cmake_minimum_required(VERSION 3.1.0)
project(tts-dev-studio)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/src)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(tts-dev-studio "src/main.cpp")
target_link_libraries(tts-dev-studio Qt5::Widgets)
