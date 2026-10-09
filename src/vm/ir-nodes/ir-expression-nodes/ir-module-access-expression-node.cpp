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
// Created by Johny Georges on 2026-03-27.
//

#include "ir-module-access-expression-node.h"
#include "../../../shared/utils/logger/logger.h"
#include "../../ir-type/ir-new-class-instance-type.h"
#include "../../ir-type/ir-class-instance-type.h"

IRModuleAccessExpressionNode::IRModuleAccessExpressionNode(std::shared_ptr<ASTModuleAccessExpressionNode> node, llvm::Value* irValue, std::shared_ptr<IRType> irType) {
    _node = node;
    _irValue = irValue;
    _irType = irType;
}

void IRModuleAccessExpressionNode::markAsGlobal() {
    _isGlobal = true;
}

std::shared_ptr<ASTModuleAccessExpressionNode> IRModuleAccessExpressionNode::getNode() {
    return _node;
}

std::shared_ptr<IRType> IRModuleAccessExpressionNode::getIRType() {
    return _irType;
}

std::shared_ptr<TypeSignature> IRModuleAccessExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRModuleAccessExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRModuleAccessExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

llvm::Value* IRModuleAccessExpressionNode::getValue() {
    return _irValue;
}

IRNodeType IRModuleAccessExpressionNode::getNodeType() {
    return IR_MODULE_ACCESS_EXPRESSION_NODE;
}

std::string IRModuleAccessExpressionNode::toString() {
    return "IR_MODULE_ACCESS_EXPRESSION_NODE";
}

void IRModuleAccessExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(llvm::outs());
}