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
        ir-generator/ir-strategies/expression-ir-strategies/binary-expression-ir-strategy/binary-expression-ir-strategy.cpp
        ir-generator/ir-strategies/expression-ir-strategies/binary-expression-ir-strategy/binary-expression-ir-strategy.h
        ir-generator/ir-strategies/expression-ir-strategies/logical-expression-ir-strategy/logical-expression-ir-strategy.cpp
        ir-generator/ir-strategies/expression-ir-strategies/logical-expression-ir-strategy/logical-expression-ir-strategy.h
        ir-generator/ir-strategies/expression-ir-strategies/array-expression-ir-strategy/array-expression-ir-strategy.cpp
        ir-generator/ir-strategies/expression-ir-strategies/array-expression-ir-strategy/array-expression-ir-strategy.h
        ir-generator/ir-strategies/type-signature-ir-strategies/array-type-signature-ir-strategy/array-type-signature-ir-strategy.cpp
        ir-generator/ir-strategies/type-signature-ir-strategies/array-type-signature-ir-strategy/array-type-signature-ir-strategy.h
        ir-generator/ir-strategies/expression-ir-strategies/array-access-expression-ir-strategy/array-access-expression-ir-strategy.cpp
        ir-generator/ir-strategies/expression-ir-strategies/array-access-expression-ir-strategy/array-access-expression-ir-strategy.h
        ir-generator/ir-strategies/expression-ir-strategies/struct-expression-ir-strategy/struct-expression-ir-strategy.cpp
        ir-generator/ir-strategies/expression-ir-strategies/struct-expression-ir-strategy/struct-expression-ir-strategy.h
        ir-type/ir-type.cpp
        ir-type/ir-type.h
        utils/address-space-generator/address-space-generator.cpp
        utils/address-space-generator/address-space-generator.h
        utils/data-alignment-generator/data-alignment-generator.cpp
        utils/data-alignment-generator/data-alignment-generator.h
        ir-generator/ir-strategies/expression-ir-strategies/unary-expression-ir-strategy/unary-expression-ir-strategy.cpp
        ir-generator/ir-strategies/expression-ir-strategies/unary-expression-ir-strategy/unary-expression-ir-strategy.h
)

target_link_libraries(jet-vm
        PRIVATE jet-core
        PRIVATE jet-shared
        PRIVATE ${llvm_libs}
)