cmake_minimum_required(VERSION 3.26)

set(LT_LLVM_INSTALL_DIR, "/usr/local/opt/llvm")
set(LT_LLVM_INCLUDE_DIR "${LT_LLVM_INSTALL_DIR}/include")
find_package(LLVM CONFIG)
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support core irreader irprinter ${LLVM_TARGETS_TO_BUILD})

set(CMAKE_EXE_LINKER_FLAGS "-lc++")
add_executable(jet ./main.cpp)
target_compile_features(jet PRIVATE cxx_std_17)
target_link_libraries(jet
        PRIVATE jet-vm
        PRIVATE jet-core
        PRIVATE jet-shared
        PRIVATE ${llvm_libs}
)
