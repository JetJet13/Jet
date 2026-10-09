// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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