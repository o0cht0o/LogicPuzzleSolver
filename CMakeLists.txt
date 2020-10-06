cmake_minimum_required(VERSION 3.5)

project(LogicPuzzleSolver)

set(CMAKE_AUTOMOC ON)

add_subdirectory(ui)

add_executable(LPS main.cpp)

target_link_libraries(LPS lpsui)
