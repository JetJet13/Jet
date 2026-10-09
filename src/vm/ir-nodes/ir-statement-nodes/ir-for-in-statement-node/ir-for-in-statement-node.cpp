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

#include "ir-for-in-statement-node.h"

IRForInStatementNode::IRForInStatementNode(std::shared_ptr<ASTForInStatementNode> node, std::shared_ptr<IRInstructionNode> index, std::shared_ptr<IRInstructionNode> variable, std::shared_ptr<IRExpressionNode> source, std::shared_ptr<IRBlockNode> setupBlock, std::shared_ptr<IRBlockNode> forInBlock, std::shared_ptr<IRBlockNode> bodyBlock, std::shared_ptr<IRBlockNode> endBlock, std::optional<std::shared_ptr<IRCapturedVariableNode>> capturedVariable) {
    _node = node;
    _index = index;
    _variable = variable;
    _source = source;
    _setupBlock = setupBlock;
    _forInBlock = forInBlock;
    _bodyBlock = bodyBlock;
    _endBlock = endBlock;
    _capturedVariable = capturedVariable;
}

std::shared_ptr<IRInstructionNode> IRForInStatementNode::getIndex() {
    return _index;
}

std::shared_ptr<IRInstructionNode> IRForInStatementNode::getVariable() {
    return _variable;
}

std::optional<std::shared_ptr<IRCapturedVariableNode>> IRForInStatementNode::getCapturedVariable() {
    return _capturedVariable;
}

std::shared_ptr<IRExpressionNode> IRForInStatementNode::getSource() {
    return _source;
}

std::shared_ptr<IRBlockNode> IRForInStatementNode::getSetupBlock() {
    return _setupBlock;
}

std::shared_ptr<IRBlockNode> IRForInStatementNode::getForInBlock() {
    return _forInBlock;
}

std::shared_ptr<IRBlockNode> IRForInStatementNode::getBodyBlock() {
    return _bodyBlock;
}

std::shared_ptr<IRBlockNode> IRForInStatementNode::getEndBlock() {
    return _endBlock;
}

void IRForInStatementNode::nestIn(std::shared_ptr<IRBlockNode> irBlock) {
    irBlock->nest(_setupBlock);
    irBlock->nest(_forInBlock);
    irBlock->nest(_bodyBlock);
    irBlock->nest(_endBlock);
}

IRNodeType IRForInStatementNode::getNodeType() {
    return IR_FOR_IN_STATEMENT_NODE;
}

std::string IRForInStatementNode::toString() {
    return "IR_FOR_IN_STATEMENT_NODE";
}

void IRForInStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _source->print(stream);
}