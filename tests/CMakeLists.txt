
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.1 # or a later release
)
FetchContent_MakeAvailable(Catch2)
set(CMAKE_EXE_LINKER_FLAGS "-lc++")
add_executable(jet-test
        core/pre-processor/lexical-analyzer/lexical-analyzer.test.cpp
        core/pre-processor/syntax-analyzer/syntax-analyzer.test.cpp
        core/pre-processor/syntax-analyzer/resources/ast-node-factory.h
        core/pre-processor/semantic-analyzer/semantic-analyzer.test.cpp
        core/pre-processor/semantic-analyzer/resources/type-signature-factory.h
        vm/ir-generator/ir-generator.test.cpp
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/core/pre-processor/lexical-analyzer/lexical-analyzer-test-file.jet
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/core/pre-processor/syntax-analyzer/syntax-analyzer-test-file.jet
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/core/pre-processor/semantic-analyzer/semantic-analyzer-test-file.jet
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vm/ir-generator/ir-generator-test-file.jet
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

set(LT_LLVM_INSTALL_DIR, "/usr/local/opt/llvm")
set(LT_LLVM_INCLUDE_DIR "${LT_LLVM_INSTALL_DIR}/include")
find_package(LLVM CONFIG)
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

target_compile_features(jet-test PRIVATE cxx_std_17)
target_link_libraries(jet-test
        PRIVATE Catch2::Catch2WithMain
        PRIVATE jet-vm
        PRIVATE jet-core
        PRIVATE jet-shared
)
