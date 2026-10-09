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

#include "ir-unary-arithmetic-expression-node.h"

IRUnaryArithmeticExpressionNode::IRUnaryArithmeticExpressionNode(std::shared_ptr<ASTUnaryExpressionNode> astNode, llvm::BinaryOperator* irValue, std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRType> type) {
    _node = astNode;
    _irValue = irValue;
    _irExpression = irExpression;
    _type = type;
}

std::shared_ptr<IRExpressionNode> IRUnaryArithmeticExpressionNode::getIRValue() {
    return _irExpression;
}

void IRUnaryArithmeticExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irExpression->markAsGlobal();
}

llvm::BinaryOperator* IRUnaryArithmeticExpressionNode::getValue() {
    return _irValue;
}

std::shared_ptr<IRType> IRUnaryArithmeticExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRUnaryArithmeticExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRUnaryArithmeticExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRUnaryArithmeticExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRUnaryArithmeticExpressionNode::getNodeType() {
    return IR_UNARY_ARITHMETIC_EXPRESSION_NODE;
}

std::string IRUnaryArithmeticExpressionNode::toString() {
    return "IR_UNARY_ARITHMETIC_EXPRESSION_NODE";
}

void IRUnaryArithmeticExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
    stream->get()->write('\n');
    _irExpression->print(stream);
}