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
// Created by Johny Georges on 2025-01-08.
//

#include "ir-if-statement-node.h"

IRIfStatementNode::IRIfStatementNode(std::shared_ptr<ASTIfStatementNode> node, std::shared_ptr<IRIfElseNode> ifElseNode, std::optional<std::shared_ptr<IRBlockNode>> elseNode) {
    _node = node;
    _ifElseNode = ifElseNode;
    _elseNode = elseNode;
}

std::shared_ptr<IRIfElseNode> IRIfStatementNode::getIfElseNode() {
    return _ifElseNode;
}

std::optional<std::shared_ptr<IRBlockNode>> IRIfStatementNode::getElseNode() {
    return _elseNode;
}

IRNodeType IRIfStatementNode::getNodeType() {
    return IR_IF_STATEMENT_NODE;
}

std::string IRIfStatementNode::toString() {
    return "IR_IF_STATEMENT_NODE";
}

void IRIfStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _ifElseNode->print(stream);
}