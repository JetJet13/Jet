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
// Created by Johny Georges on 2024-07-01.
//

#include "ir-unary-negate-expression-node.h"

IRUnaryNegateExpressionNode::IRUnaryNegateExpressionNode(std::shared_ptr<ASTUnaryExpressionNode> node, std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRType> type) {
    _node = node;
    _irExpression = irExpression;
    _type = type;
}

std::shared_ptr<IRExpressionNode> IRUnaryNegateExpressionNode::getIRExpression() {
    return _irExpression;
}

void IRUnaryNegateExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irExpression->markAsGlobal();
}

llvm::Value* IRUnaryNegateExpressionNode::getValue() {
    return _irExpression->getValue();
}

std::shared_ptr<IRType> IRUnaryNegateExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRUnaryNegateExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRUnaryNegateExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRUnaryNegateExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRUnaryNegateExpressionNode::getNodeType() {
    return IR_UNARY_NEGATE_EXPRESSION_NODE;
}

std::string IRUnaryNegateExpressionNode::toString() {
    return "IR_UNARY_NEGATE_EXPRESSION_NODE";
}

void IRUnaryNegateExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irExpression->print(stream);
}