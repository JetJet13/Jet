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

#include "ir-char-literal-node.h"

IRCharLiteralNode::IRCharLiteralNode(std::shared_ptr<ASTCharLiteralNode> astNode, llvm::ConstantInt* irValue) {
    _astNode = astNode;
    _irValue = irValue;
    _type = std::make_shared<IRType>(_irValue->getType());
}

llvm::ConstantInt* IRCharLiteralNode::getConstantIRValue() {
    return _irValue;
}

std::shared_ptr<IRType> IRCharLiteralNode::getIRType() {
    return _type;
}

IRNodeType IRCharLiteralNode::getNodeType() {
    return IR_CHAR_LITERAL_NODE;
}

std::string IRCharLiteralNode::toString() {
    return "IR_CHAR_LITERAL_NODE";
}

void IRCharLiteralNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}