cmake_minimum_required(VERSION 3.26)

#set(CMAKE_BUILD_TYPE Debug)
#add_compile_options(-fsanitize=address,undefined)
#add_compile_options(-fno-rtti)
#add_link_options(-fsanitize=address,undefined)

find_package(LLVM CONFIG)
find_package(LLD CONFIG)

message(STATUS "--------------------------------------------------------")
message(STATUS "[LLVM CONFIG DETECTION]")
message(STATUS "  LLVM Found:           ${LLVM_FOUND}")
message(STATUS "  LLVM Version:         ${LLVM_PACKAGE_VERSION}")
message(STATUS "  LLVM Config File:     ${LLVM_DIR}")
message(STATUS "  LLVM Include Dirs:    ${LLVM_INCLUDE_DIRS}")
message(STATUS "  LLVM Library Dirs:    ${LLVM_LIBRARY_DIRS}")

message(STATUS "[LLD CONFIG DETECTION]")
message(STATUS "  LLD Found:            ${LLD_FOUND}")
message(STATUS "  LLD Config File:      ${LLD_DIR}")
message(STATUS "  LLD Include Dirs:     ${LLD_INCLUDE_DIRS}")
message(STATUS "--------------------------------------------------------")

message(STATUS "Found LLVM: ${LLVM_DIR}")
message(STATUS "LLVM Assertions: ${LLVM_ENABLE_ASSERTIONS}")
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS} ${LLD_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS} ${LLD_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support core linker irreader irprinter ${LLVM_TARGETS_TO_BUILD})


set(CMAKE_EXE_LINKER_FLAGS "-lc++")
add_executable(jet main.cpp main.h
        types/target-helper.cpp
        types/target-helper.h
        types/supported-targets.h
        types/supported-llvm-targets.h
        cli11/CLI11.hpp
        types/linker-arg-builder.cpp
        types/linker-arg-builder.h
        types/cli-helper.cpp
        types/cli-helper.h)
target_compile_features(jet PRIVATE cxx_std_17)
target_link_libraries(jet
        PRIVATE jet-vm
        PRIVATE jet-core
        PRIVATE jet-shared
        PRIVATE lldCommon
        PRIVATE lldCOFF
        PRIVATE lldELF
        PRIVATE lldMachO
        PRIVATE lldMinGW
        PRIVATE lldWasm
        PRIVATE ${llvm_libs}
)

add_executable(jet-debug debug-main.cpp debug-main.h
        types/target-helper.cpp
        types/target-helper.h
        types/supported-targets.h
        types/supported-llvm-targets.h
        cli11/CLI11.hpp
        types/linker-arg-builder.cpp
        types/linker-arg-builder.h
        types/cli-helper.cpp
        types/cli-helper.h
)
target_compile_features(jet-debug PRIVATE cxx_std_17)
target_link_libraries(jet-debug
        PRIVATE jet-vm
        PRIVATE jet-core
        PRIVATE jet-shared
        PRIVATE lldCommon
        PRIVATE lldCOFF
        PRIVATE lldELF
        PRIVATE lldMachO
        PRIVATE lldMinGW
        PRIVATE lldWasm
        PRIVATE ${llvm_libs}
)

add_executable(jet-cli jet-cli.cpp jet-cli.h cli11/CLI11.hpp)
target_compile_features(jet-cli PRIVATE cxx_std_17)
