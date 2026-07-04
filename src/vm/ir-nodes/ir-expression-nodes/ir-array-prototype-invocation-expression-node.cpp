//
// Created by Johny Georges on 2025-06-16.
//

#include "ir-array-prototype-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRArrayPrototypeInvocationExpressionNode::IRArrayPrototypeInvocationExpressionNode(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> node, llvm::Value* irFunction, llvm::CallInst* irCallInstruction, IRType* irFunctionType, std::vector<IRFunctionArgumentNode*> arguments, IRType* type, IRExpressionNode* irArray) {
    _node = node;
    _irCallInstruction = irCallInstruction;
    _irFunction = irFunction;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
    _irArray = irArray;
}

void IRArrayPrototypeInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->getArgument()->markAsGlobal();
    }
}

bool IRArrayPrototypeInvocationExpressionNode::requiresTypeValueArgument() {
    return this->getValue()->getFunctionType()->getNumParams() > 1;
}

IRExpressionNode* IRArrayPrototypeInvocationExpressionNode::getIRArrayValue() {
    return _irArray;
}

std::vector<IRFunctionArgumentNode*>* IRArrayPrototypeInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::CallInst* IRArrayPrototypeInvocationExpressionNode::getValue() {
    return _irCallInstruction;
}


llvm::Value* IRArrayPrototypeInvocationExpressionNode::getFunctionValue() {
    return _irFunction;
}

IRType* IRArrayPrototypeInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

IRType* IRArrayPrototypeInvocationExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRArrayPrototypeInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRArrayPrototypeInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRArrayPrototypeInvocationExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRArrayPrototypeInvocationExpressionNode::getNodeType() {
    return IR_ARRAY_PROTOTYPE_INVOCATION_EXPRESSION_NODE;
}

std::string IRArrayPrototypeInvocationExpressionNode::toString() {
    return "IR_ARRAY_PROTOTYPE_INVOCATION_EXPRESSION_NODE";
}

void IRArrayPrototypeInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->print(**stream);
}