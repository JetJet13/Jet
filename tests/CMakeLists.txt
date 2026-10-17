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
llvm_map_components_to_libnames(llvm_libs support core linker irreader irprinter ${LLVM_TARGETS_TO_BUILD})

Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)
set(CMAKE_EXE_LINKER_FLAGS "-lc++")
add_executable(jet-test
        core/pre-processor/syntax-analyzer/syntax-analyzer.test.cpp
        core/pre-processor/syntax-analyzer/utils/ast-node-factory.h
        core/pre-processor/semantic-analyzer/semantic-analyzer.test.cpp
        core/pre-processor/semantic-analyzer/utils/type-signature-factory.h
        vm/vm.test.cpp
        vm/utils/ir-equality-checker/ir-equality-checker.cpp
        vm/utils/ir-equality-checker/ir-equality-checker.h
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/core/pre-processor/syntax-analyzer/syntax-analyzer-test-file.jet
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/core/pre-processor/semantic-analyzer/semantic-analyzer-test-file.jet
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(vm/vm-test-expected-output.ir
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/jet/golden-master-test-file.jet
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/jet/other-test-file.jet
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/jet/second-test-file.jet
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/jet/struct-test-file.jet
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/jet/third-test-file.jet
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/jet/fourth-test-file.jet
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/jet/main-test-file.jet
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/jet/big-module.jet
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/jet/arc-test-file.jet
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)


target_compile_features(jet-test PRIVATE cxx_std_17)
target_link_libraries(jet-test
        PRIVATE Catch2::Catch2WithMain
        PRIVATE jet-vm
        PRIVATE jet-core
        PRIVATE jet-shared
        PRIVATE ${llvm_libs}
)
