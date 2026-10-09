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
// Created by Johny Georges on 2026-03-16.
//

#include "ir-class-static-method-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRClassStaticMethodInvocationExpressionNode::IRClassStaticMethodInvocationExpressionNode(std::shared_ptr<ASTObjectAccessInvocationExpressionNode> node, std::shared_ptr<IRInstructionNode> irFunction, llvm::CallInst* irCallInstruction, std::shared_ptr<IRType> irFunctionType, std::vector<std::shared_ptr<IRFunctionArgumentNode>> arguments, std::shared_ptr<IRType> type) {
    _node = node;
    _irCallInstruction = irCallInstruction;
    _irFunction = irFunction;
    _irFunctionType = irFunctionType;
    _arguments = arguments;
    _type = type;
}

void IRClassStaticMethodInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->getArgument()->markAsGlobal();
    }
}

std::shared_ptr<IRInstructionNode> IRClassStaticMethodInvocationExpressionNode::getFunction() {
    return _irFunction;
}

std::vector<std::shared_ptr<IRFunctionArgumentNode>>* IRClassStaticMethodInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::CallInst* IRClassStaticMethodInvocationExpressionNode::getValue() {
    return _irCallInstruction;
}

llvm::Value* IRClassStaticMethodInvocationExpressionNode::getFunctionValue() {
    return _irFunction->getValue();
}

std::shared_ptr<IRType> IRClassStaticMethodInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

std::shared_ptr<IRType> IRClassStaticMethodInvocationExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRClassStaticMethodInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRClassStaticMethodInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRClassStaticMethodInvocationExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRClassStaticMethodInvocationExpressionNode::getNodeType() {
    return IR_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_NODE;
}

std::string IRClassStaticMethodInvocationExpressionNode::toString() {
    return "IR_CLASS_STATIC_METHOD_INVOCATION_EXPRESSION_NODE";
}

void IRClassStaticMethodInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->getValue()->print(**stream);
}