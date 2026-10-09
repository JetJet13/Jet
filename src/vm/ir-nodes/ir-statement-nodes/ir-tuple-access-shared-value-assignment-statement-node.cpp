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

#include "ir-tuple-access-shared-value-assignment-statement-node.h"

IRTupleAccessSharedValueAssignmentStatementNode::IRTupleAccessSharedValueAssignmentStatementNode(std::shared_ptr<ASTTupleAccessSharedValueAssignmentStatementNode> node, std::shared_ptr<IRTupleAccessExpressionNode> irTupleAccessExpression, std::shared_ptr<IRExpressionNode> irExpression) {
    _node = node;
    _irTupleAccessExpression = irTupleAccessExpression;
    _irExpression = irExpression;
}

std::shared_ptr<IRTupleAccessExpressionNode> IRTupleAccessSharedValueAssignmentStatementNode::getIRTupleAccessExpression() {
    return _irTupleAccessExpression;
}

std::shared_ptr<IRExpressionNode> IRTupleAccessSharedValueAssignmentStatementNode::getIRExpression() {
    return _irExpression;
}

IRNodeType IRTupleAccessSharedValueAssignmentStatementNode::getNodeType() {
    return IR_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE;
}

std::string IRTupleAccessSharedValueAssignmentStatementNode::toString() {
    return "IR_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE";
}

void IRTupleAccessSharedValueAssignmentStatementNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irTupleAccessExpression->print(stream);
    _irExpression->print(stream);
}