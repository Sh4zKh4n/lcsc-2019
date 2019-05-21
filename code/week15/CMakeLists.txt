cmake_minimum_required(VERSION 3.8)
project(test_range)

add_subdirectory("ext/catch2")


add_executable(test_range "src/test.cpp")
target_compile_features(test_range PUBLIC cxx_std_17)
target_compile_options(test_range PUBLIC
    "-Wfatal-errors"
    "-Werror"
    "-Wall"
    "-O3")
target_include_directories(test_range PUBLIC "include")
target_link_libraries(test_range Catch2::Catch2)
