//
// Created by Johny Georges on 2026-02-14.
//

#ifndef JETLANG_BINARY_ARITHMETIC_DSU_H
#define JETLANG_BINARY_ARITHMETIC_DSU_H

#include <llvm/IR/Value.h>
#include "../../ir-nodes/ir-expression-nodes/ir-expression-node.h"

// Binary Arithmetic Disjoint-Set-Union
class BinaryArithmeticDSU : public std::enable_shared_from_this<BinaryArithmeticDSU> {
private:
    llvm::Value* _irValue;
    std::optional<std::shared_ptr<BinaryArithmeticDSU>> _parent;
    std::vector<std::shared_ptr<BinaryArithmeticDSU>> _children;
public:
    BinaryArithmeticDSU(llvm::Value* irValue);
    llvm::Value* getValue();
    void merge(std::shared_ptr<BinaryArithmeticDSU> other);
    void setParent(std::shared_ptr<BinaryArithmeticDSU> parent);
};

#endif //JETLANG_BINARY_ARITHMETIC_DSU_H
