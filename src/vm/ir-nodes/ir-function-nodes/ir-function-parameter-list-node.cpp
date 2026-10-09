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
// Created by Johny Georges on 2024-07-08.
//

#include "ir-function-parameter-list-node.h"

IRFunctionParameterListNode::IRFunctionParameterListNode(std::shared_ptr<ASTFunctionParameterListNode> node, std::vector<std::shared_ptr<IRFunctionParameterNode>> parameters) {
    _node = node;
    _parameters = parameters;
    _scopeParameter = {};
}

void IRFunctionParameterListNode::addLambdaScopeParameter(std::shared_ptr<IRFunctionParameterNode> parameter) {
    _scopeParameter = parameter;
}

std::optional<std::shared_ptr<IRFunctionParameterNode>> IRFunctionParameterListNode::getLambdaScopeParameter() {
    return _scopeParameter;
}

std::vector<std::shared_ptr<IRFunctionParameterNode>>* IRFunctionParameterListNode::getParameters() {
    return &_parameters;
}

void IRFunctionParameterListNode::addClassScopeParameter(std::shared_ptr<IRFunctionParameterNode> classScopeParameter) {
    _parameters.push_back(classScopeParameter);
}

std::vector<llvm::Argument*> IRFunctionParameterListNode::getArguments() {
    auto arguments = std::vector<llvm::Argument*>();
    for (auto parameter : _parameters) {
        arguments.push_back(parameter->getArgument());
    }
    return arguments;
}

IRNodeType IRFunctionParameterListNode::getNodeType() {
    return IR_FUNCTION_PARAMETER_LIST_NODE;
}

std::string IRFunctionParameterListNode::toString() {
    return "IR_FUNCTION_PARAMETER_LIST_NODE";
}

void IRFunctionParameterListNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    for (auto parameter : _parameters) {
        parameter->print(stream);
    }
}