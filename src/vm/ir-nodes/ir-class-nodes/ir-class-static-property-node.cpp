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
// Created by Johny Georges on 2026-03-14.
//

#include "ir-class-static-property-node.h"

IRClassStaticPropertyNode::IRClassStaticPropertyNode(std::shared_ptr<ASTClassPropertyDeclarationNode> node, llvm::GlobalVariable* irValue, std::shared_ptr<IRExpressionNode> initialIRValue, std::shared_ptr<IRType> irType) {
    _node = node;
    _irValue = irValue;
    _initialIRValue = initialIRValue;
    _irType = irType;
}

llvm::GlobalVariable* IRClassStaticPropertyNode::getGlobalVariable() {
    return _irValue;
}

std::shared_ptr<IRExpressionNode> IRClassStaticPropertyNode::getInitialIRValue() {
    return _initialIRValue;
}

std::shared_ptr<IRType> IRClassStaticPropertyNode::getIRType() {
    return _irType;
}