cmake_minimum_required(VERSION 3.8)

project(lcsc_data)

# we use an external JSON library
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(ext/json)

set(LIB_SOURCES
  "src/report.cpp"
  "src/timer.cpp"
)
add_library(lcsc_data ${LIB_SOURCES})

target_include_directories(lcsc_data PUBLIC "include")
target_compile_features(lcsc_data PUBLIC cxx_std_17)
target_link_libraries(lcsc_data PRIVATE nlohmann_json::nlohmann_json)

target_compile_options(lcsc_data PUBLIC
    "-Wfatal-errors"
    "-Werror"
    "-Wall"
    "-O3")

add_executable(plot "example/plot.cpp")
target_link_libraries(plot lcsc_data)

add_executable(table "example/table.cpp")
target_link_libraries(table lcsc_data)

