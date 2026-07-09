//
// Created by Johny Georges on 2026-02-14.
//

#include "binary-arithmetic-dsu.h"


BinaryArithmeticDSU::BinaryArithmeticDSU(llvm::Value* irValue) {
    _irValue = irValue;
    _children = std::vector<std::shared_ptr<BinaryArithmeticDSU>>();
}

llvm::Value* BinaryArithmeticDSU::getValue() {
    if (_parent) {
        return _parent.value()->getValue();
    }
    return _irValue;
}

void BinaryArithmeticDSU::merge(std::shared_ptr<BinaryArithmeticDSU> other) {
    other->setParent(shared_from_this());
    _children.push_back(other);
}

void BinaryArithmeticDSU::setParent(std::shared_ptr<BinaryArithmeticDSU> parent) {
    _parent = parent;
}
