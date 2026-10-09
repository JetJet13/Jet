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
// Created by Johny Georges on 2024-03-14.
//

#ifndef JETLANG_AST_OBJECT_ACCESS_EXPRESSION_NODE_H
#define JETLANG_AST_OBJECT_ACCESS_EXPRESSION_NODE_H

#include <string>
#include "../ast-object-nodes/ast-object-access-source-node.h"
#include "../ast-object-nodes/ast-object-access-target-node.h"
#include "../ast-period-node.h"
#include "ast-aggregate-expression-node.h"

class ASTObjectAccessExpressionNode : public ASTAggregateExpressionNode {
private:
    std::shared_ptr<ASTObjectAccessSourceNode> _source;
    std::shared_ptr<ASTPeriodNode> _period;
    std::shared_ptr<ASTObjectAccessTargetNode> _target;
public:
    ASTObjectAccessExpressionNode(std::shared_ptr<ASTObjectAccessSourceNode> source, std::shared_ptr<ASTPeriodNode> period, std::shared_ptr<ASTObjectAccessTargetNode> property);
    std::shared_ptr<ASTObjectAccessSourceNode> getSource();
    std::shared_ptr<ASTObjectAccessTargetNode> getTarget();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_OBJECT_ACCESS_EXPRESSION_NODE_H
