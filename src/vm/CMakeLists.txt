set(LT_LLVM_INSTALL_DIR, "/usr/local/opt/llvm")
set(LT_LLVM_INCLUDE_DIR "${LT_LLVM_INSTALL_DIR}/include")
find_package(LLVM CONFIG)
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
add_definitions(${LLVM_DEFINITIONS})
llvm_map_components_to_libnames(llvm_libs support core irreader irprinter)

add_library(jet-vm
        ./ir-generator/ir-generator.cpp
        ./ir-generator/ir-generator.h
        ./ir-generator/ir-lookup-table/ir-lookup-table.cpp
        ./ir-generator/ir-lookup-table/ir-lookup-table.h
        ir-generator/ir-strategies/literal-ir-strategies/int-literal-ir-strategy/int-literal-ir-strategy.cpp
        ir-generator/ir-strategies/literal-ir-strategies/int-literal-ir-strategy/int-literal-ir-strategy.h
        ir-generator/ir-strategies/literal-ir-strategies/float-literal-ir-strategy/float-literal-ir-strategy.cpp
        ir-generator/ir-strategies/literal-ir-strategies/float-literal-ir-strategy/float-literal-ir-strategy.h
        ir-generator/ir-strategies/literal-ir-strategies/char-literal-ir-strategy/char-literal-ir-strategy.cpp
        ir-generator/ir-strategies/literal-ir-strategies/char-literal-ir-strategy/char-literal-ir-strategy.h
        ir-generator/ir-strategies/literal-ir-strategies/string-literal-ir-strategy/string-literal-ir-strategy.cpp
        ir-generator/ir-strategies/literal-ir-strategies/string-literal-ir-strategy/string-literal-ir-strategy.h
        ir-generator/ir-strategies/literal-ir-strategies/bool-literal-ir-strategy/bool-literal-ir-strategy.cpp
        ir-generator/ir-strategies/literal-ir-strategies/bool-literal-ir-strategy/bool-literal-ir-strategy.h
        ir-generator/ir-strategies/ir-strategy-map.cpp
        ir-generator/ir-strategies/ir-strategy-map.h
)

target_link_libraries(jet-vm
        PRIVATE jet-core
        PRIVATE jet-shared
        PRIVATE ${llvm_libs}
)