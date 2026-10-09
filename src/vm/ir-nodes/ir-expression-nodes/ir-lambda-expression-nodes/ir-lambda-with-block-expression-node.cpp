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
// Created by Johny Georges on 2024-11-12.
//

#include "ir-lambda-with-block-expression-node.h"

IRLambdaWithBlockExpressionNode::IRLambdaWithBlockExpressionNode(std::shared_ptr<ASTLambdaExpressionNode> node, std::shared_ptr<IRInstructionNode> irValue, llvm::Function* irFunction, std::shared_ptr<IRFunctionParameterListNode> irParameterList, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRLambdaType> type, llvm::Function* irCleanupFunction) {
    _node = node;
    _irValue = irValue;
    _irFunction = irFunction;
    _irParameterList = irParameterList;
    _irBlock = irBlock;
    _type = type;
    _irCleanupFunction = irCleanupFunction;
}

llvm::Function* IRLambdaWithBlockExpressionNode::getCleanupFunction() {
    return _irCleanupFunction;
}

std::shared_ptr<IRFunctionParameterListNode> IRLambdaWithBlockExpressionNode::getParameters() {
    return _irParameterList;
}

std::shared_ptr<IRBlockNode> IRLambdaWithBlockExpressionNode::getBlock() {
    return _irBlock;
}

llvm::Value* IRLambdaWithBlockExpressionNode::getValue() {
    return _irValue->getValue();
}

std::shared_ptr<IRInstructionNode> IRLambdaWithBlockExpressionNode::getAllocation() {
    return _irValue;
}

llvm::Function* IRLambdaWithBlockExpressionNode::getFunctionValue() {
    return _irFunction;
}

std::shared_ptr<IRType> IRLambdaWithBlockExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRLambdaWithBlockExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRLambdaWithBlockExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRLambdaWithBlockExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRLambdaWithBlockExpressionNode::getNodeType() {
    return IR_LAMBDA_WITH_BLOCK_EXPRESSION_NODE;
}

std::string IRLambdaWithBlockExpressionNode::toString() {
    return "IR_LAMBDA_WITH_BLOCK_EXPRESSION_NODE";
}

void IRLambdaWithBlockExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irFunction->print(**stream);
}