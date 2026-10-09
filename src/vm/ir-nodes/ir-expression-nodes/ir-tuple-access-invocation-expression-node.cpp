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
// Created by Johny Georges on 2025-06-19.
//

#include "ir-tuple-access-invocation-expression-node.h"
#include "../../../shared/utils/logger/logger.h"

IRTupleAccessInvocationExpressionNode::IRTupleAccessInvocationExpressionNode(std::shared_ptr<ASTTupleAccessInvocationExpressionNode> node, std::shared_ptr<IRExpressionNode> source, llvm::CallInst* irCallInstruction, std::shared_ptr<IRType> irFunctionType, int64_t targetIndex, std::vector<std::shared_ptr<IRFunctionArgumentNode>> arguments, std::shared_ptr<IRType> type) {
    _node = node;
    _source = source;
    _irCallInstruction = irCallInstruction;
    _irFunctionType = irFunctionType;
    _targetIndex = targetIndex;
    _arguments = arguments;
    _type = type;
}

void IRTupleAccessInvocationExpressionNode::markAsGlobal() {
    _isGlobal = true;
    for (auto argument : _arguments) {
        argument->getArgument()->markAsGlobal();
    }
}

std::shared_ptr<IRExpressionNode> IRTupleAccessInvocationExpressionNode::getSource() {
    return _source;
}

std::vector<std::shared_ptr<IRFunctionArgumentNode>>* IRTupleAccessInvocationExpressionNode::getIRArguments() {
    return &_arguments;
}

llvm::CallInst* IRTupleAccessInvocationExpressionNode::getValue() {
    return _irCallInstruction;
}

std::shared_ptr<IRType> IRTupleAccessInvocationExpressionNode::getFunctionIRType() {
    return _irFunctionType;
}

int64_t IRTupleAccessInvocationExpressionNode::getTargetIndex() {
    return _targetIndex;
}

std::shared_ptr<IRType> IRTupleAccessInvocationExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRTupleAccessInvocationExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRTupleAccessInvocationExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRTupleAccessInvocationExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

IRNodeType IRTupleAccessInvocationExpressionNode::getNodeType() {
    return IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE;
}

std::string IRTupleAccessInvocationExpressionNode::toString() {
    return "IR_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE";
}

void IRTupleAccessInvocationExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irCallInstruction->print(**stream);
}