//
// Created by Johny Georges on 2026-02-14.
//

#ifndef JETLANG_BINARY_ARITHMETIC_DSU_H
#define JETLANG_BINARY_ARITHMETIC_DSU_H

#include <llvm/IR/Value.h>
#include "ir-expression-nodes/ir-expression-node.h"

// Binary Arithmetic Disjoint-Set-Union
class BinaryArithmeticDSU {
private:
    llvm::Value* _irValue;
    std::optional<BinaryArithmeticDSU*> _parent;
    std::vector<BinaryArithmeticDSU*> _children;
public:
    BinaryArithmeticDSU(llvm::Value* irValue);
    llvm::Value* getValue();
    void merge(BinaryArithmeticDSU* other);
    void setParent(BinaryArithmeticDSU* parent);
};

#endif //JETLANG_BINARY_ARITHMETIC_DSU_H
