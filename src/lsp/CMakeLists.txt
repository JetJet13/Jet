cmake_minimum_required(VERSION 3.26)
project("jet-lsp")


find_package(LLVM CONFIG)
message(STATUS "--------------------------------------------------------")
message(STATUS "[LLVM CONFIG DETECTION]")
message(STATUS "  LLVM Found:           ${LLVM_FOUND}")
message(STATUS "  LLVM Version:         ${LLVM_PACKAGE_VERSION}")
message(STATUS "  LLVM Config File:     ${LLVM_DIR}")
message(STATUS "  LLVM Include Dirs:    ${LLVM_INCLUDE_DIRS}")
message(STATUS "  LLVM Library Dirs:    ${LLVM_LIBRARY_DIRS}")
message(STATUS "--------------------------------------------------------")
message(STATUS "Found LLVM: ${LLVM_DIR}")
message(STATUS "LLVM Assertions: ${LLVM_ENABLE_ASSERTIONS}")
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support core linker irreader irprinter)

add_library(lspcpp STATIC IMPORTED)
set_target_properties(lspcpp PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../../zig-util/target/x86_64-macos/lspcpp/lib/liblspcpp.a"
)
target_include_directories(lspcpp
    INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/../../zig-util/target/x86_64-macos/lspcpp/include"
)

set(CMAKE_EXE_LINKER_FLAGS "-lc++")
add_executable(jet-lsp lsp.cpp lsp.h
        utils/lsp-logger.cpp
        utils/lsp-logger.h
        custom/set-trace-notification.h)
target_compile_features(jet-lsp PRIVATE cxx_std_17)

target_link_libraries(jet-lsp
        PRIVATE jet-core
        PRIVATE jet-shared
        PRIVATE ${llvm_libs}
        PRIVATE lspcpp
)