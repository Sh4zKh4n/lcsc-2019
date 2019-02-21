# We want CMake >= 3.8 so that we can set the C++ standard using compile_features
cmake_minimum_required(VERSION 3.8)

# The name of the project
project(lcsc)

# Add a TestU01 target
link_directories("ext/TestU01/lib")
add_library(TestU01 INTERFACE)
target_include_directories(TestU01 INTERFACE "ext/TestU01/include")
target_link_libraries(TestU01 INTERFACE mylib probdist testu01)

# Define a target 'lcsc' for our (RNG) library.
set(LIB_SOURCES
  "src/rng/util.cpp"
)
add_library(lcsc ${LIB_SOURCES})

# Set the include directory, and force >= C++14
target_include_directories(lcsc PUBLIC "include")
target_compile_features(lcsc PUBLIC cxx_std_14)
target_link_libraries(lcsc PUBLIC TestU01)

# We set a number of useful compile flags that enables optimizations, and a
# better set of errors and warnings
target_compile_options(lcsc PUBLIC
    "-Wfatal-errors"
    "-Werror"
    "-Wall"
    "-O3")

# We only have on executable, that prints a number of randomly generated numbers
# Multiple executables can be added
add_executable(print_rng "example/print_rng.cpp")
target_link_libraries(print_rng lcsc)

add_executable(test_rng "example/test_rng.cpp")
target_link_libraries(test_rng lcsc)

add_executable(test_histogram "example/test_histogram.cpp")
target_link_libraries(test_histogram lcsc)

