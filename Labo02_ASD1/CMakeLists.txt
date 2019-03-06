cmake_minimum_required(VERSION 3.13)
project(Labo02_ASD1)

set(CMAKE_CXX_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wconversion -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_executable(Labo02_ASD1 main.cpp pieces.cpp pieces.h)