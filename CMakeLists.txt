cmake_minimum_required(VERSION 3.26)
project(jetlang)

add_subdirectory(src/shared)
add_subdirectory(src/core)
add_subdirectory(src/vm)
add_subdirectory(src/jet)
add_subdirectory(tests)