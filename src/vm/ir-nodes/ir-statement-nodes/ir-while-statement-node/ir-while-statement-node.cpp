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
// Created by Johny Georges on 2025-05-24.
//

#include "ir-while-statement-node.h"

IRWhileStatementNode::IRWhileStatementNode(std::shared_ptr<ASTWhileStatementNode> node, std::shared_ptr<IRExpressionNode> condition, std::shared_ptr<IRBlockNode> whileBlock, std::shared_ptr<IRBlockNode> bodyBlock, std::shared_ptr<IRBlockNode> endBlock) {
    _condition = condition;
    _whileBlock = whileBlock;
    _bodyBlock = bodyBlock;
    _endBlock = endBlock;
}

std::shared_ptr<IRExpressionNode> IRWhileStatementNode::getExpression() {
    return _condition;
}

std::shared_ptr<IRBlockNode> IRWhileStatementNode::getWhileBlock() {
    return _whileBlock;
}

std::shared_ptr<IRBlockNode> IRWhileStatementNode::getBodyBlock() {
    return _bodyBlock;
}

std::shared_ptr<IRBlockNode> IRWhileStatementNode::getEndBlock() {
    return _endBlock;
}

void IRWhileStatementNode::nestIn(std::shared_ptr<IRBlockNode> irBlock) {
    irBlock->nest(_whileBlock);
    irBlock->nest(_bodyBlock);
    irBlock->nest(_endBlock);
}

IRNodeType IRWhileStatementNode::getNodeType() {
    return IR_WHILE_STATEMENT_NODE;
}

std::string IRWhileStatementNode::toString() {
    return "IR_WHILE_STATEMENT_NODE";
}

void IRWhileStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _condition->print(stream);
}