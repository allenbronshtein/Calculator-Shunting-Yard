cmake_minimum_required(VERSION 3.15)
project(myProject)

set(CMAKE_CXX_STANDARD 11)

add_executable(myProject main.cpp ex1.cpp ex1.h Expression.h interpreter.h interpret.cpp)