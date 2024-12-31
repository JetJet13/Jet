//
// Created by Johny Georges on 2024-12-30.
//

#include "ir-new-class-instance-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRNewClassInstanceExpressionNode::IRNewClassInstanceExpressionNode(ASTNewClassInstanceExpressionNode* node, llvm::Value* irConstructor, IRType* irConstructorType, std::vector<IRExpressionNode*> arguments, IRType* type) {
    _node = node;
    _irConstructor = irConstructor;
    _irConstructorType = irConstructorType;
    _arguments = arguments;
    _type = type;
}

std::vector<IRExpressionNode*>* IRNewClassInstanceExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::Value* IRNewClassInstanceExpressionNode::getValue() {
    return _irConstructor;
}

IRType* IRNewClassInstanceExpressionNode::getConstructorIRType() {
    return _irConstructorType;
}

IRType* IRNewClassInstanceExpressionNode::getIRType() {
    return _type;
}

ClassInstanceTypeSignature* IRNewClassInstanceExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

IRNodeType IRNewClassInstanceExpressionNode::getNodeType() {
    return IR_FUNCTION_INVOCATION_EXPRESSION_NODE;
}

std::string IRNewClassInstanceExpressionNode::toString() {
    return "IR_FUNCTION_INVOCATION_EXPRESSION_NODE";
}

void IRNewClassInstanceExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irConstructor->print(**stream);
}