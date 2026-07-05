//
// Created by Johny Georges on 2024-07-02.
//

#include "ir-expression-node.h"
#include "../../ir-type/ir-ref-type.h"
#include "../../../shared/utils/logger/logger.h"

void IRExpressionNode::markAsGlobal() {
    _isGlobal = true;
}

bool IRExpressionNode::isGlobal() {
    return _isGlobal;
}

bool IRExpressionNode::isAssigned() {
    return _isAssigned;
}

void IRExpressionNode::markAsAssigned() {
    _isAssigned = true;
}

bool IRExpressionNode::isReturned() {
    return _isReturned;
}

void IRExpressionNode::markAsReturned() {
    _isReturned = true;
}

bool IRExpressionNode::isGrouped() {
    return _isGrouped;
}

void IRExpressionNode::markAsGrouped() {
    _isGrouped = true;
}

bool IRExpressionNode::needsToBeFreed() {
    return !this->isGlobal() &&
           !this->isAssigned() &&
           !this->isReturned() &&
           !this->isOneOf({
               IR_THIS_EXPRESSION_NODE,
               IR_IDENTIFIER_EXPRESSION_NODE,
               IR_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE,
               IR_OBJECT_ACCESS_EXPRESSION_NODE,
               IR_TUPLE_ACCESS_EXPRESSION_NODE,
               IR_ARRAY_ACCESS_EXPRESSION_NODE,
               IR_MODULE_ACCESS_EXPRESSION_NODE
           }) &&
           this->getIRType()->containsTypeThatRequiresFreeing();
}

bool IRExpressionNode::hasArc() {
    return this->getArc().has_value();
}

std::shared_ptr<IRType> IRExpressionNode::getUnderlyingIRType() {
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

std::optional<IRInstructionNode*> IRExpressionNode::getArc() {
    return {};
}

bool IRExpressionNode::isExpression() {
    return true;
}

llvm::Type* IRExpressionNode::getType() {
    return this->getValue()->getType();
}

llvm::Type* IRExpressionNode::getTypeAtIndex(unsigned long index) {
    return this->getValue()->getType();
}