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
// Created by Johny Georges on 2025-02-17.
//

#include "ir-array-access-assignment-statement-node.h"

IRArrayAccessAssignmentStatementNode::IRArrayAccessAssignmentStatementNode(std::shared_ptr<ASTArrayAccessAssignmentStatementNode> node, std::shared_ptr<IRArrayAccessExpressionNode> irArrayAccessExpression, std::shared_ptr<IRExpressionNode> irExpression) {
    _node = node;
    _irArrayAccessExpression = irArrayAccessExpression;
    _irExpression = irExpression;
}

std::shared_ptr<IRArrayAccessExpressionNode> IRArrayAccessAssignmentStatementNode::getIRArrayAccessExpression() {
    return _irArrayAccessExpression;
}

std::shared_ptr<IRExpressionNode> IRArrayAccessAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRArrayAccessAssignmentStatementNode::getNodeType() {
    return IR_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRArrayAccessAssignmentStatementNode::toString() {
    return "IR_ARRAY_ACCESS_ASSIGNMENT_STATEMENT_NODE";
}

void IRArrayAccessAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irArrayAccessExpression->print(stream);
    _irExpression->print(stream);
}