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

bool IRExpressionNode::isReferenced() {
    return false;
}

bool IRExpressionNode::isAssigned() {
    return _assignedTo.has_value();
}

void IRExpressionNode::assignTo(llvm::Value* value) {
    _assignedTo = value;
}

bool IRExpressionNode::needsToBeFreed() {
    return !this->isReferenced() &&
           !this->isGlobal() &&
           !this->isAssigned() &&
           !this->isOneOf({
               IR_IDENTIFIER_EXPRESSION_NODE,
               IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE,
               IR_OBJECT_ACCESS_EXPRESSION_NODE,
               IR_TUPLE_ACCESS_EXPRESSION_NODE,
               IR_ARRAY_ACCESS_EXPRESSION_NODE
           }) &&
           this->getIRType()->containsTypeThatRequiresFreeing();
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