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

#ifndef JETLANG_IR_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_IR_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H

#include "../ir-expression-nodes/ir-expression-node.h"
#include "ir-statement-node.h"
#include "../ir-expression-nodes/ir-tuple-access-expression-node.h"
#include "../../../core/ast/ast-nodes/ast-statement-nodes/ast-tuple-access-shared-value-assignment-statement-node.h"

class IRTupleAccessSharedValueAssignmentStatementNode : public IRStatementNode {
private:
    std::shared_ptr<ASTTupleAccessSharedValueAssignmentStatementNode> _node;
    std::shared_ptr<IRTupleAccessExpressionNode> _irTupleAccessExpression;
    std::shared_ptr<IRExpressionNode> _irExpression;
public:
    IRTupleAccessSharedValueAssignmentStatementNode(std::shared_ptr<ASTTupleAccessSharedValueAssignmentStatementNode> node, std::shared_ptr<IRTupleAccessExpressionNode> irTupleAccessExpression, std::shared_ptr<IRExpressionNode> irExpression);
    std::shared_ptr<IRTupleAccessExpressionNode> getIRTupleAccessExpression();
    std::shared_ptr<IRExpressionNode> getIRExpression();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_TUPLE_ACCESS_SHARED_VALUE_ASSIGNMENT_STATEMENT_NODE_H
