cmake_minimum_required(VERSION 3.8)
project(range)

add_executable(range "range.cpp")
target_compile_options(range PUBLIC
    "-Wfatal-errors"
    "-Werror"
    "-Wall"
    "-O3")
