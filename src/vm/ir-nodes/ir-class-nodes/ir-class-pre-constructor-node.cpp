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
// Created by Johny Georges on 2025-12-27.
//

#include "ir-class-pre-constructor-node.h"

IRClassPreConstructorNode::IRClassPreConstructorNode(llvm::Function* irValue, std::shared_ptr<IRInstructionNode> classScopeParameter, std::vector<std::pair<uint64_t, std::shared_ptr<IRExpressionNode>>> irExpressions, std::vector<std::pair<uint64_t, llvm::Constant*>> irInitializers, std::shared_ptr<IRBlockNode> irBlock) {
    _irValue = irValue;
    _classScopeParameter = classScopeParameter;
    _irExpressions = irExpressions;
    _irInitializers = irInitializers;
    _irBlock = irBlock;
}

llvm::Function* IRClassPreConstructorNode::getFunction() {
    return _irValue;
}

std::vector<std::pair<uint64_t, std::shared_ptr<IRExpressionNode>>>* IRClassPreConstructorNode::getExpressions() {
    return &_irExpressions;
}

std::vector<std::pair<uint64_t, llvm::Constant*>>* IRClassPreConstructorNode::getInitializers() {
    return &_irInitializers;
}

std::shared_ptr<IRInstructionNode> IRClassPreConstructorNode::getClassScopeParameter() {
    return _classScopeParameter;
}

std::shared_ptr<IRBlockNode> IRClassPreConstructorNode::getBlock() {
    return _irBlock;
}