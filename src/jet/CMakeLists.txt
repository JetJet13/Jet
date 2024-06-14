cmake_minimum_required(VERSION 3.26)

set(CMAKE_EXE_LINKER_FLAGS "-lc++")
add_executable(jet ./main.cpp)
target_compile_features(jet PRIVATE cxx_std_17)
target_link_libraries(jet
        PRIVATE jet-vm
        PRIVATE jet-core
        PRIVATE jet-shared
)
