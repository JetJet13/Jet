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
// Created by Johny Georges on 2024-06-29.
//

#include "ir-string-literal-node.h"

IRStringLiteralNode::IRStringLiteralNode(std::shared_ptr<ASTStringLiteralNode> astNode, llvm::Constant* irValue, std::shared_ptr<IRArrayType> type) {
    _astNode = astNode;
    _irValue = irValue;
    _type = type;
}

llvm::Constant* IRStringLiteralNode::getConstantIRValue() {
    return _irValue;
}

std::shared_ptr<IRArrayType> IRStringLiteralNode::getIRArrayType() {
    return _type;
}

std::shared_ptr<IRType> IRStringLiteralNode::getIRType() {
    return _type;
}

IRNodeType IRStringLiteralNode::getNodeType() {
    return IR_STRING_LITERAL_NODE;
}

std::string IRStringLiteralNode::toString() {
    return "IR_STRING_LITERAL_NODE";
}

void IRStringLiteralNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}