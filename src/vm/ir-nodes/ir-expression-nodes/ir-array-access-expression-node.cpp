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
// Created by Johny Georges on 2024-07-06.
//

#include "ir-array-access-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRArrayAccessExpressionNode::IRArrayAccessExpressionNode(std::shared_ptr<ASTArrayAccessExpressionNode> node, std::shared_ptr<IRExpressionNode> irSource, std::shared_ptr<IRExpressionNode> irIndex, std::shared_ptr<IRType> type, std::optional<std::shared_ptr<IRInstructionNode>> sourceAllocation) {
    _node = node;
    _irSource = irSource;
    _irIndex = irIndex;
    _type = type;
    _sourceAllocation = sourceAllocation;
}

void IRArrayAccessExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irSource->markAsGlobal();
    _irIndex->markAsGlobal();
}


std::shared_ptr<IRExpressionNode> IRArrayAccessExpressionNode::getSourceExpression() {
    return _irSource;
}

std::shared_ptr<IRExpressionNode> IRArrayAccessExpressionNode::getIndexExpression() {
    return _irIndex;
}

std::shared_ptr<ASTArrayAccessExpressionNode> IRArrayAccessExpressionNode::getNode() {
    return _node;
}

std::optional<std::shared_ptr<IRInstructionNode>> IRArrayAccessExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
}

llvm::Value* IRArrayAccessExpressionNode::getValue() {
    return _irSource->getValue();
}

std::shared_ptr<IRType> IRArrayAccessExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRArrayAccessExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRArrayAccessExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRArrayAccessExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRArrayAccessExpressionNode::getNodeType() {
    return IR_ARRAY_ACCESS_EXPRESSION_NODE;
}

std::string IRArrayAccessExpressionNode::toString() {
    return "IR_ARRAY_ACCESS_EXPRESSION_NODE";
}

void IRArrayAccessExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irSource->print(stream);
    _irIndex->print(stream);
}