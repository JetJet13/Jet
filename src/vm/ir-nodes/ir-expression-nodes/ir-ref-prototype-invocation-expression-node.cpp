//
// Created by Johny Georges on 2025-10-25.
//

#include "ir-ref-prototype-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRRefPrototypeInvocationExpressionNode::IRRefPrototypeInvocationExpressionNode(ASTObjectAccessInvocationExpressionNode* node, llvm::Value* irFunction, IRType* irFunctionType, std::vector<IRExpressionNode*> arguments, IRType* type, IRExpressionNode* irRef) {
    _node = node;
    _irFunction = irFunction;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
    _irRef = irRef;
}

void IRRefPrototypeInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->markAsGlobal();
    }
}

bool IRRefPrototypeInvocationExpressionNode::isReferenced() {
    return _node->isReferenced();
}

IRExpressionNode* IRRefPrototypeInvocationExpressionNode::getIRRefValue() {
    return _irRef;
}

std::vector<IRExpressionNode*>* IRRefPrototypeInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::Value* IRRefPrototypeInvocationExpressionNode::getValue() {
    return _irFunction;
}

IRType* IRRefPrototypeInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

IRType* IRRefPrototypeInvocationExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRRefPrototypeInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRRefPrototypeInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRRefPrototypeInvocationExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRRefPrototypeInvocationExpressionNode::getNodeType() {
    return IR_REF_PROTOTYPE_INVOCATION_EXPRESSION_NODE;
}

std::string IRRefPrototypeInvocationExpressionNode::toString() {
    return "IR_REF_PROTOTYPE_INVOCATION_EXPRESSION_NODE";
}

void IRRefPrototypeInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->print(**stream);
}