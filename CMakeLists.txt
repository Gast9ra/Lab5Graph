cmake_minimum_required(VERSION 3.14)
project(Lab5Graph C)

set(CMAKE_C_STANDARD 11)

add_executable(Lab5Graph main.c graph.c graph.h)

project(LibGraph)
set(CMAKE_C_STANDARD 11)
add_library(LibGraph STATIC
        graph.c graph.h)


project(Test C)
set(CMAKE_C_STANDARD 11)
add_executable(Test testModule.c graph.c graph.h)