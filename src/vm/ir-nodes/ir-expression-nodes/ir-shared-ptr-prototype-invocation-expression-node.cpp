//
// Created by Johny Georges on 2025-10-25.
//

#include "ir-shared-ptr-prototype-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRSharedPtrPrototypeInvocationExpressionNode::IRSharedPtrPrototypeInvocationExpressionNode(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> node, llvm::Value* irFunction, llvm::CallInst* irCallInstruction, std::shared_ptr<IRType> irFunctionType, std::vector<std::shared_ptr<IRFunctionArgumentNode>> arguments, std::shared_ptr<IRType> type, std::shared_ptr<IRExpressionNode> irSharedValue) {
    _node = node;
    _irCallInstruction = irCallInstruction;
    _irFunction = irFunction;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
    _irSharedValue = irSharedValue;
}

void IRSharedPtrPrototypeInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->getArgument()->markAsGlobal();
    }
}

std::shared_ptr<IRExpressionNode> IRSharedPtrPrototypeInvocationExpressionNode::getIRSharedValue() {
    return _irSharedValue;
}

std::vector<std::shared_ptr<IRFunctionArgumentNode>>* IRSharedPtrPrototypeInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::CallInst* IRSharedPtrPrototypeInvocationExpressionNode::getValue() {
    return _irCallInstruction;
}

llvm::Value* IRSharedPtrPrototypeInvocationExpressionNode::getFunctionValue() {
    return _irFunction;
}

std::shared_ptr<IRType> IRSharedPtrPrototypeInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

std::shared_ptr<IRType> IRSharedPtrPrototypeInvocationExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRSharedPtrPrototypeInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRSharedPtrPrototypeInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRSharedPtrPrototypeInvocationExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRSharedPtrPrototypeInvocationExpressionNode::getNodeType() {
    return IR_SHARED_PTR_PROTOTYPE_INVOCATION_EXPRESSION_NODE;
}

std::string IRSharedPtrPrototypeInvocationExpressionNode::toString() {
    return "IR_SHARED_PROTOTYPE_INVOCATION_EXPRESSION_NODE";
}

void IRSharedPtrPrototypeInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->print(**stream);
}