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
// Created by Johny Georges on 2026-02-06.
//

#include "ir-array-access-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRArrayAccessInvocationExpressionNode::IRArrayAccessInvocationExpressionNode(std::shared_ptr<ASTArrayAccessInvocationExpressionNode> node, std::shared_ptr<IRArrayAccessExpressionNode> irArrayAccessExpression, llvm::CallInst* irCallInstruction, std::shared_ptr<IRType> irFunctionType, std::vector<std::shared_ptr<IRFunctionArgumentNode>> arguments, std::shared_ptr<IRType> type) {
    _node = node;
    _irCallInstruction = irCallInstruction;
    _irArrayAccessExpression = irArrayAccessExpression;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
}

void IRArrayAccessInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->getArgument()->markAsGlobal();
    }
}

std::shared_ptr<IRArrayAccessExpressionNode> IRArrayAccessInvocationExpressionNode::getIRArrayAccessExpression() {
    return _irArrayAccessExpression;
}

std::vector<std::shared_ptr<IRFunctionArgumentNode>>* IRArrayAccessInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::CallInst* IRArrayAccessInvocationExpressionNode::getValue() {
    return _irCallInstruction;
}

std::shared_ptr<IRType> IRArrayAccessInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

std::shared_ptr<IRType> IRArrayAccessInvocationExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRArrayAccessInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRArrayAccessInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRArrayAccessInvocationExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRArrayAccessInvocationExpressionNode::getNodeType() {
    return IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE;
}

std::string IRArrayAccessInvocationExpressionNode::toString() {
    return "IR_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE";
}

void IRArrayAccessInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irArrayAccessExpression->getValue()->print(**stream);
}