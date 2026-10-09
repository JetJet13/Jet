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
// Created by Johny Georges on 2024-11-14.
//

#include "ir-lambda-with-fat-arrow-expression-node.h"

IRLambdaWithFatArrowExpressionNode::IRLambdaWithFatArrowExpressionNode(std::shared_ptr<ASTLambdaWithFatArrowExpressionNode> node, std::shared_ptr<IRInstructionNode> irValue, llvm::Function* irFunction, std::shared_ptr<IRFunctionParameterListNode> irParameterList, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRLambdaType> type, llvm::Function* irCleanupFunction, std::shared_ptr<IRExpressionNode> irReturnExpression) {
    _node = node;
    _irValue = irValue;
    _irFunction = irFunction;
    _irParameterList = irParameterList;
    _irBlock = irBlock;
    _irReturnExpression = irReturnExpression;
    _type = type;
    _irCleanupFunction = irCleanupFunction;
}

llvm::Function* IRLambdaWithFatArrowExpressionNode::getCleanupFunction() {
    return _irCleanupFunction;
}

std::shared_ptr<IRBlockNode> IRLambdaWithFatArrowExpressionNode::getBlock() {
    return _irBlock;
}

std::shared_ptr<IRExpressionNode> IRLambdaWithFatArrowExpressionNode::getReturnExpression() {
    return _irReturnExpression;
}

std::shared_ptr<IRInstructionNode> IRLambdaWithFatArrowExpressionNode::getAllocation() {
    return _irValue;
}

llvm::Function* IRLambdaWithFatArrowExpressionNode::getFunctionValue() {
    return _irFunction;
}

std::shared_ptr<IRFunctionParameterListNode> IRLambdaWithFatArrowExpressionNode::getParameters() {
    return _irParameterList;
}

llvm::Value* IRLambdaWithFatArrowExpressionNode::getValue() {
    return _irValue->getValue();
}

std::shared_ptr<IRType> IRLambdaWithFatArrowExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRLambdaWithFatArrowExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRLambdaWithFatArrowExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRLambdaWithFatArrowExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRLambdaWithFatArrowExpressionNode::getNodeType() {
    return IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE;
}

std::string IRLambdaWithFatArrowExpressionNode::toString() {
    return "IR_LAMBDA_WITH_FAT_ARROW_EXPRESSION_NODE";
}

void IRLambdaWithFatArrowExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->print(**stream);
}