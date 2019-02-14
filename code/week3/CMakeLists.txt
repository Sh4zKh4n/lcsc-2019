# We want CMake >= 3.8 so that we can set the C++ standard using compile_features
cmake_minimum_required(VERSION 3.8)

# The name of the project
project(lcsc)

# Define a target 'lcsc' for our (RNG) library. For our purposes, we can
# interpret INTERFACE as indicating that this is a library that consists solely
# of headers
add_library(lcsc INTERFACE)

# Set the include directory, and force >= C++14
target_include_directories(lcsc INTERFACE "include")
target_compile_features(lcsc INTERFACE cxx_std_14)

# We set a number of useful compile flags that enables optimizations, and a
# better set of errors and warnings
target_compile_options(lcsc INTERFACE
    "-Wfatal-errors"
    "-Werror"
    "-Wall"
    "-O3")

# We only have on executable, that prints a number of randomly generated numbers
# Multiple executables can be added
add_executable(print_rng "example/print_rng.cpp")
target_link_libraries(print_rng lcsc)
