//
// Created by Johny Georges on 2024-12-30.
//

#include "ir-new-class-instance-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRNewClassInstanceExpressionNode::IRNewClassInstanceExpressionNode(ASTNewClassInstanceExpressionNode* node, llvm::Value* irConstructor, IRFunctionType* irConstructorType, std::vector<IRExpressionNode*> arguments, IRClassType* type) {
    _node = node;
    _irConstructor = irConstructor;
    _irConstructorType = irConstructorType;
    _arguments = arguments;
    _type = type;
}

void IRNewClassInstanceExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->markAsGlobal();
    }
}

std::vector<IRExpressionNode*>* IRNewClassInstanceExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::Value* IRNewClassInstanceExpressionNode::getValue() {
    return _irConstructor;
}

IRFunctionType* IRNewClassInstanceExpressionNode::getConstructorIRType() {
    return _irConstructorType;
}

llvm::Value* IRNewClassInstanceExpressionNode::getConstructorFunction() {
    return _irConstructor;
}

IRClassType* IRNewClassInstanceExpressionNode::getIRType() {
    return _type;
}

ClassInstanceTypeSignature* IRNewClassInstanceExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

IRNodeType IRNewClassInstanceExpressionNode::getNodeType() {
    return IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE;
}

std::string IRNewClassInstanceExpressionNode::toString() {
    return "IR_NEW_CLASS_INSTANCE_EXPRESSION_NODE";
}

void IRNewClassInstanceExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irConstructor->print(**stream);
}