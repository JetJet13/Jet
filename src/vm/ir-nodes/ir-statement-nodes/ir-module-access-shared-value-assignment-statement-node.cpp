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

#include "ir-module-access-shared-value-assignment-statement-node.h"

IRModuleAccessSharedValueAssignmentStatementNode::IRModuleAccessSharedValueAssignmentStatementNode(std::shared_ptr<ASTModuleAccessSharedValueAssignmentStatementNode> node, std::shared_ptr<IRModuleAccessExpressionNode> irModuleAccessExpression, std::shared_ptr<IRExpressionNode> irExpression) {
    _node = node;
    _irModuleAccessExpression = irModuleAccessExpression;
    _irExpression = irExpression;
}

std::shared_ptr<IRModuleAccessExpressionNode> IRModuleAccessSharedValueAssignmentStatementNode::getIRModuleAccessExpression() {
    return _irModuleAccessExpression;
}

std::shared_ptr<IRExpressionNode> IRModuleAccessSharedValueAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRModuleAccessSharedValueAssignmentStatementNode::getNodeType() {
    return IR_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRModuleAccessSharedValueAssignmentStatementNode::toString() {
    return "IR_MODULE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE";
}

void IRModuleAccessSharedValueAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irModuleAccessExpression->print(stream);
    _irExpression->print(stream);
}