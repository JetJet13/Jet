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
// Created by Johny Georges on 2026-06-27.
//

#include "ir-object-access-shared-value-assignment-statement-node.h"

IRObjectAccessSharedValueAssignmentStatementNode::IRObjectAccessSharedValueAssignmentStatementNode(std::shared_ptr<ASTObjectAccessSharedValueAssignmentStatementNode> node, std::shared_ptr<IRObjectAccessExpressionNode> irObjectAccessExpression, std::shared_ptr<IRExpressionNode> irExpression) {
    _node = node;
    _irObjectAccessExpression = irObjectAccessExpression;
    _irExpression = irExpression;
}

std::shared_ptr<IRObjectAccessExpressionNode> IRObjectAccessSharedValueAssignmentStatementNode::getIRObjectAccessExpression() {
    return _irObjectAccessExpression;
}

std::shared_ptr<IRExpressionNode> IRObjectAccessSharedValueAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRObjectAccessSharedValueAssignmentStatementNode::getNodeType() {
    return IR_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRObjectAccessSharedValueAssignmentStatementNode::toString() {
    return "IR_OBJECT_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE";
}

void IRObjectAccessSharedValueAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irObjectAccessExpression->print(stream);
    _irExpression->print(stream);
}