//
// Created by Johny Georges on 2025-10-25.
//

#include "ir-ref-prototype-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRRefPrototypeInvocationExpressionNode::IRRefPrototypeInvocationExpressionNode(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> node, llvm::Value* irFunction, llvm::CallInst* irCallInstruction, std::shared_ptr<IRType> irFunctionType, std::vector<std::shared_ptr<IRFunctionArgumentNode>> arguments, std::shared_ptr<IRType> type, std::shared_ptr<IRExpressionNode> irRef) {
    _node = node;
    _irCallInstruction = irCallInstruction;
    _irFunction = irFunction;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
    _irRef = irRef;
}

void IRRefPrototypeInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->getArgument()->markAsGlobal();
    }
}

std::shared_ptr<IRExpressionNode> IRRefPrototypeInvocationExpressionNode::getIRRefValue() {
    return _irRef;
}

std::vector<std::shared_ptr<IRFunctionArgumentNode>>* IRRefPrototypeInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::CallInst* IRRefPrototypeInvocationExpressionNode::getValue() {
    return _irCallInstruction;
}

llvm::Value* IRRefPrototypeInvocationExpressionNode::getFunctionValue() {
    return _irFunction;
}

std::shared_ptr<IRType> IRRefPrototypeInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

std::shared_ptr<IRType> IRRefPrototypeInvocationExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRRefPrototypeInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRRefPrototypeInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRRefPrototypeInvocationExpressionNode::getEndPosition() {
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