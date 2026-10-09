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
// Created by Johny Georges on 2024-07-13.
//

#include "ir-function-parameter-node.h"

IRFunctionParameterNode::IRFunctionParameterNode(llvm::Argument* irValue, std::shared_ptr<IRParameterType> parameterType, std::shared_ptr<IRInstructionNode> allocation, std::optional<std::shared_ptr<ASTFunctionParameterNode>> node, std::optional<std::shared_ptr<IRInstructionNode>> irArc) {
    _irValue = irValue;
    _parameterType = parameterType;
    _allocation = allocation;
    _node = node;
    _irArc = irArc;
}

llvm::Argument* IRFunctionParameterNode::getArgument() {
    return _irValue;
}

std::shared_ptr<IRParameterType> IRFunctionParameterNode::getParameterType() {
    return _parameterType;
}

std::shared_ptr<IRInstructionNode> IRFunctionParameterNode::getAllocation() {
    return _allocation;
}

std::optional<std::shared_ptr<IRInstructionNode>> IRFunctionParameterNode::getArc() {
    return _irArc;
}

bool IRFunctionParameterNode::isCaptured() {
    if (!_node) return false;
    return _node.value()->isCaptured();
}

uint64_t IRFunctionParameterNode::getCaptureCount() {
    if (!_node) return 0;
    return _node.value()->getCaptureCount();
}

bool IRFunctionParameterNode::needsToBeFreed() {
    if (!_node) return false;
    return !_node.value()->isCaptured() &&
            _parameterType->getIRType()->containsTypeThatRequiresFreeing();
}

IRNodeType IRFunctionParameterNode::getNodeType() {
    return IR_FUNCTION_PARAMETER_NODE;
}

std::string IRFunctionParameterNode::toString() {
    return "IR_FUNCTION_PARAMETER_NODE";
}

void IRFunctionParameterNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}