//
// Created by Johny Georges on 2024-12-30.
//

#include "ir-new-class-instance-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRNewClassInstanceExpressionNode::IRNewClassInstanceExpressionNode(ASTNewClassInstanceExpressionNode* node, llvm::Value* irConstructor, IRFunctionType* irConstructorType, std::vector<IRExpressionNode*> arguments, IRClassInstanceType* type, IRInstructionNode* classInstanceAllocation) {
    _node = node;
    _irConstructor = irConstructor;
    _irConstructorType = irConstructorType;
    _arguments = arguments;
    _type = type;
    _classInstanceAllocation = classInstanceAllocation;
}

void IRNewClassInstanceExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->markAsGlobal();
    }
}

bool IRNewClassInstanceExpressionNode::isReferenced() {
    return _node->isReferenced();
}


IRInstructionNode* IRNewClassInstanceExpressionNode::getClassInstanceAllocation() {
    return _classInstanceAllocation;
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

IRClassInstanceType* IRNewClassInstanceExpressionNode::getIRType() {
    return _type;
}

ClassInstanceTypeSignature* IRNewClassInstanceExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRNewClassInstanceExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRNewClassInstanceExpressionNode::getEndPosition() {
    return _node->getEndPosition();
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