//
// Created by Johny Georges on 2024-07-02.
//

#include "ir-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

void IRExpressionNode::markAsGlobal() {
    _isGlobal = true;
}

bool IRExpressionNode::isGlobal() {
    return _isGlobal;
}

TypeSource IRExpressionNode::getInjectorTypeSource() {
    auto typeSignature = this->getTypeSignature();
    if (typeSignature->typeSourceIs(POINTER_TYPE_SOURCE)) {
        return POINTER_TYPE_SOURCE;
    }
    return typeSignature->getTypeTarget();
}

std::optional<IRInstructionNode*> IRExpressionNode::getSourceAllocation() {
    return {};
}

llvm::Type* IRExpressionNode::getType() {
    return this->getValue()->getType();
}

llvm::Type* IRExpressionNode::getTypeAtIndex(unsigned long index) {
    return this->getValue()->getType();
}