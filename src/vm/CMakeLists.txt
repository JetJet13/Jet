set(LT_LLVM_INSTALL_DIR, "/usr/local/opt/llvm")
set(LT_LLVM_INCLUDE_DIR "${LT_LLVM_INSTALL_DIR}/include")
find_package(LLVM CONFIG)
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_library(jet-vm
        ./ir-generator/ir-generator.cpp
        ./ir-generator/ir-generator.h
        ./ir-generator/ir-lookup-table/ir-lookup-table.cpp
        ./ir-generator/ir-lookup-table/ir-lookup-table.h
)

target_link_libraries(jet-vm
        PRIVATE jet-core
        PRIVATE jet-shared
        PRIVATE LLVMSupport
)