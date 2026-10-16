cmake_minimum_required(VERSION 3.26)
project("jet-cli")

add_subdirectory(../shared ${CMAKE_CURRENT_BINARY_DIR}/jet-shared-build)
add_executable(jet-cli jet-cli.cpp jet-cli.h)
target_compile_features(jet-cli PRIVATE cxx_std_17)
target_link_libraries(jet-cli PRIVATE jet-shared)
