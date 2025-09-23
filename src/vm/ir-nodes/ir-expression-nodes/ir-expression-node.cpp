//
// Created by Johny Georges on 2024-07-02.
//

#include "ir-expression-node.h"
#include "../../ir-type/ir-ref-type.h"

void IRExpressionNode::markAsGlobal() {
    _isGlobal = true;
}

bool IRExpressionNode::isGlobal() {
    return _isGlobal;
}

bool IRExpressionNode::requiresFreeing() {
    return this->getIRType()->containsTypeThatRequiresFreeing();
}

IRType* IRExpressionNode::getUnderlyingIRType() {
    return this->getIRType()->getUnderlyingType();
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