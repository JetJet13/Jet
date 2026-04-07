//
// Created by Johny Georges on 2026-02-14.
//

#include "binary-arithmetic-dsu.h"


BinaryArithmeticDSU::BinaryArithmeticDSU(llvm::Value* irValue) {
    _irValue = irValue;
    _children = std::vector<BinaryArithmeticDSU*>();
}

llvm::Value* BinaryArithmeticDSU::getValue() {
    if (_parent) {
        return _parent.value()->getValue();
    }
    return _irValue;
}

void BinaryArithmeticDSU::merge(BinaryArithmeticDSU* other) {
    other->setParent(this);
    _children.push_back(other);
}

void BinaryArithmeticDSU::setParent(BinaryArithmeticDSU* parent) {
    _parent = parent;
}
