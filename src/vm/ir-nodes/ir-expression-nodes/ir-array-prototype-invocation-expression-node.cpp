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
// Created by Johny Georges on 2025-06-16.
//

#include "ir-array-prototype-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRArrayPrototypeInvocationExpressionNode::IRArrayPrototypeInvocationExpressionNode(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> node, llvm::Value* irFunction, llvm::CallInst* irCallInstruction, std::shared_ptr<IRType> irFunctionType, std::vector<std::shared_ptr<IRFunctionArgumentNode>> arguments, std::shared_ptr<IRType> type, std::shared_ptr<IRExpressionNode> irArray) {
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

std::shared_ptr<IRExpressionNode> IRArrayPrototypeInvocationExpressionNode::getIRArrayValue() {
    return _irArray;
}

std::vector<std::shared_ptr<IRFunctionArgumentNode>>* IRArrayPrototypeInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::CallInst* IRArrayPrototypeInvocationExpressionNode::getValue() {
    return _irCallInstruction;
}


llvm::Value* IRArrayPrototypeInvocationExpressionNode::getFunctionValue() {
    return _irFunction;
}

std::shared_ptr<IRType> IRArrayPrototypeInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

std::shared_ptr<IRType> IRArrayPrototypeInvocationExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRArrayPrototypeInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRArrayPrototypeInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRArrayPrototypeInvocationExpressionNode::getEndPosition() {
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