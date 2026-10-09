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

#include "ir-bool-literal-node.h"

IRBoolLiteralNode::IRBoolLiteralNode(std::shared_ptr<ASTBooleanLiteralNode> astNode, llvm::ConstantInt* irValue) {
    _astNode = astNode;
    _irValue = irValue;
    _type = std::make_shared<IRType>(_irValue->getType());
}

llvm::ConstantInt* IRBoolLiteralNode::getConstantIRValue() {
    return _irValue;
}

std::shared_ptr<IRType> IRBoolLiteralNode::getIRType() {
    return _type;
}

IRNodeType IRBoolLiteralNode::getNodeType() {
    return IR_BOOL_LITERAL_NODE;
}

std::string IRBoolLiteralNode::toString() {
    return "IR_BOOL_LITERAL_NODE";
}

void IRBoolLiteralNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
}