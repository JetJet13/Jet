cmake_minimum_required(VERSION 3.26)

#set(CMAKE_BUILD_TYPE Debug)
#add_compile_options(-fsanitize=address,undefined)
#add_compile_options(-fno-rtti)
#add_link_options(-fsanitize=address,undefined)

set(LT_LLVM_INSTALL_DIR, "/Users/johny.georges/Documents/software/llvm-project-17.0.6.src/build")
set(LT_LLVM_INCLUDE_DIR "${LT_LLVM_INSTALL_DIR}/include")
find_package(LLVM CONFIG)
message(STATUS "Found LLVM: ${LLVM_DIR}")
message(STATUS "LLVM Assertions: ${LLVM_ENABLE_ASSERTIONS}")
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support core linker irreader irprinter ${LLVM_TARGETS_TO_BUILD})

set(CMAKE_EXE_LINKER_FLAGS "-lc++")
add_executable(jet
        main.cpp
        main.h)
target_compile_features(jet PRIVATE cxx_std_17)
target_link_libraries(jet
        PRIVATE jet-vm
        PRIVATE jet-core
        PRIVATE jet-shared
        PRIVATE ${llvm_libs}
)

add_executable(jet-debug debug-main.cpp debug-main.h)
target_compile_features(jet-debug PRIVATE cxx_std_17)
target_link_libraries(jet-debug
        PRIVATE jet-vm
        PRIVATE jet-core
        PRIVATE jet-shared
        PRIVATE ${llvm_libs}
)
