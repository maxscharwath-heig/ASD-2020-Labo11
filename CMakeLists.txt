cmake_minimum_required(VERSION 3.15)
project(ASD1_Labs_2020)

set(CMAKE_CXX_STANDARD 14)

add_executable(bst_main main.cpp)
add_subdirectory(catch2_tests)
