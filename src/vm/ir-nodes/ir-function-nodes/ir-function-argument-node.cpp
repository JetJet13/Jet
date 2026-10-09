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
// Created by Johny Georges on 2026-02-09.
//

#include "ir-function-argument-node.h"

IRFunctionArgumentNode::IRFunctionArgumentNode(std::shared_ptr<IRExpressionNode> irArgument) {
    _irArgument = irArgument;
    _irOperation = std::make_shared<IROperation>(IR_FUNCTION_ARGUMENT_OP);
}

IRFunctionArgumentNode::IRFunctionArgumentNode(std::shared_ptr<IRExpressionNode> irArgument, std::shared_ptr<IROperation> irOperation) {
    _irArgument = irArgument;
    _irOperation = irOperation;
}

std::shared_ptr<IRExpressionNode> IRFunctionArgumentNode::getArgument() {
    return _irArgument;
}

std::shared_ptr<IROperation> IRFunctionArgumentNode::getOperation() {
    return _irOperation;
}

IRNodeType IRFunctionArgumentNode::getNodeType() {
    return IR_FUNCTION_ARGUMENT_NODE;
}

std::string IRFunctionArgumentNode::toString() {
    return "IR_FUNCTION_ARGUMENT_NODE";
}

void IRFunctionArgumentNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irArgument->print(stream);
}