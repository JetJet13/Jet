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
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "ast-array-expression-node.h"
#include "../ast-array-nodes/ast-array-access-node.h"
#include "../ast-class-nodes/ast-class-property-access-node.h"

class ASTClassPropertyAccessExpressionNode : public ASTExpressionNode {
private:
    std::shared_ptr<ASTClassPropertyAccessNode> _propertyAccess;
public:
    ASTClassPropertyAccessExpressionNode(std::shared_ptr<ASTClassPropertyAccessNode> propertyAccess);
    std::shared_ptr<ASTClassPropertyAccessNode> getPropertyAccess();
    std::string getPropertyName();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_ACCESS_EXPRESSION_NODE_H
