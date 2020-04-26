cmake_minimum_required(VERSION 3.16)
project(MultiplicatorComparison)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3")

add_executable(MultiplicationComparison main.cpp large-integer.h multiplicator.h)