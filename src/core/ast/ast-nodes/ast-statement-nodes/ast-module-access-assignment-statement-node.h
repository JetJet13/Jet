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
// Created by Johny Georges on 2026-04-02.
//

#ifndef JETLANG_AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
#define JETLANG_AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-object-nodes/ast-object-access-assignment-node.h"
#include "ast-statement-node.h"
#include "../ast-module-nodes/ast-module-access-assignment-node.h"

class ASTModuleAccessAssignmentStatementNode : public ASTStatementNode {
private:
    std::shared_ptr<ASTModuleAccessAssignmentNode> _moduleAccessAssignment;
    std::shared_ptr<ASTExpressionNode> _expression;
public:
    ASTModuleAccessAssignmentStatementNode(std::shared_ptr<ASTModuleAccessAssignmentNode> moduleAccessAssignment, std::shared_ptr<ASTExpressionNode> expression);
    std::shared_ptr<ASTModuleAccessAssignmentNode> getModuleAccessAssignment();
    std::shared_ptr<ASTExpressionNode> getExpression();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_ACCESS_ASSIGNMENT_STATEMENT_NODE_H
