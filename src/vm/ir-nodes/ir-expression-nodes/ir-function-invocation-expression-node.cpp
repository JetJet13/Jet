//
// Created by Johny Georges on 2024-11-08.
//

#include "ir-function-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRFunctionInvocationExpressionNode::IRFunctionInvocationExpressionNode(std::shared_ptr<ASTFunctionInvocationExpressionNode> node, std::shared_ptr<IRInstructionNode> irFunction, llvm::CallInst* irCallInstruction, std::shared_ptr<IRType> irFunctionType, std::vector<std::shared_ptr<IRFunctionArgumentNode>> arguments, std::shared_ptr<IRType> type, std::optional<std::shared_ptr<IRInstructionNode>> varArgsTypeValueArgument) {
    _node = node;
    _irCallInstruction = irCallInstruction;
    _irFunction = irFunction;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
    _varArgsTypeValueArgument = varArgsTypeValueArgument;
}

void IRFunctionInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->getArgument()->markAsGlobal();
    }
}

std::optional<std::shared_ptr<IRInstructionNode>> IRFunctionInvocationExpressionNode::getVarArgsTypeValueArgument() {
    return _varArgsTypeValueArgument;
}

std::vector<std::shared_ptr<IRFunctionArgumentNode>>* IRFunctionInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

std::shared_ptr<ASTFunctionInvocationExpressionNode> IRFunctionInvocationExpressionNode::getNode() {
    return _node;
}

llvm::CallInst* IRFunctionInvocationExpressionNode::getValue() {
    return _irCallInstruction;
}

std::shared_ptr<IRInstructionNode> IRFunctionInvocationExpressionNode::getFunction() {
    return _irFunction;
}

llvm::Value* IRFunctionInvocationExpressionNode::getFunctionValue() {
    return _irFunction->getValue();
}

std::shared_ptr<IRType> IRFunctionInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

std::shared_ptr<IRType> IRFunctionInvocationExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<FunctionInvocationTypeSignature> IRFunctionInvocationExpressionNode::getInvocationTypeSignature() {
    return _node->getInvocationTypeSignature();
}

std::shared_ptr<TypeSignature> IRFunctionInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRFunctionInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRFunctionInvocationExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRFunctionInvocationExpressionNode::getNodeType() {
    return IR_FUNCTION_INVOCATION_EXPRESSION_NODE;
}

std::string IRFunctionInvocationExpressionNode::toString() {
    return "IR_FUNCTION_INVOCATION_EXPRESSION_NODE";
}

void IRFunctionInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->getValue()->print(**stream);
}