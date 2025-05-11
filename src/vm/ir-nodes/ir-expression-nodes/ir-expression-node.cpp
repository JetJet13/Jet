//
// Created by Johny Georges on 2024-07-02.
//

#include "ir-expression-node.h"

void IRExpressionNode::markAsGlobal() {
    _isGlobal = true;
}

bool IRExpressionNode::isGlobal() {
    return _isGlobal;
}

bool IRExpressionNode::requiresFreeing() {
    return this->getIRType()->containsTypeThatRequiresFreeing();
}

TypeSource IRExpressionNode::getInjectorTypeSource() {
    auto typeSignature = this->getTypeSignature();
    if (typeSignature->typeSourceIs(REF_TYPE_SOURCE)) {
        return REF_TYPE_SOURCE;
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