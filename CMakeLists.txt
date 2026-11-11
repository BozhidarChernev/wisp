
cmake_minimum_required(VERSION 3.21)

project(Wisp
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Wisp
    src/main.cpp

    src/app/MainWindow.h
    src/app/MainWindow.cpp
)

target_link_libraries(Wisp
    PRIVATE
    Qt6::Widgets
)
