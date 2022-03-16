cmake_minimum_required(VERSION 2.8)

project(lab1sem3)

add_library(c-rational c-rational.cpp)

add_library(cpp-rational cpp-rational.cpp)

add_executable(main main.cpp)

target_link_libraries(main c-rational cpp-rational)
