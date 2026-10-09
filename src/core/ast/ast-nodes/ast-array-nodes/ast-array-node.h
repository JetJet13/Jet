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
// Created by Johny Georges on 2024-03-11.
//

#ifndef JETLANG_AST_ARRAY_NODE_H
#define JETLANG_AST_ARRAY_NODE_H

#include <optional>
#include <string>
#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "ast-left-bracket-node.h"
#include "ast-right-bracket-node.h"
#include "../ast-comma-node.h"

class ASTArrayNode : public ASTNode {
private:
    std::shared_ptr<ASTLeftBracketNode> _leftBracket;
    std::shared_ptr<ASTRightBracketNode> _rightBracket;
    std::vector<std::shared_ptr<ASTCommaNode>> _commas;
    std::vector<std::shared_ptr<ASTExpressionNode>> _elements;
public:
    explicit ASTArrayNode(std::shared_ptr<ASTLeftBracketNode> leftBracket, std::shared_ptr<ASTRightBracketNode> rightBracket);
    explicit ASTArrayNode(std::shared_ptr<ASTLeftBracketNode> leftBracket, std::vector<std::shared_ptr<ASTExpressionNode>> elements, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTRightBracketNode> rightBracket);
    std::shared_ptr<ASTArrayNode> addElement(std::shared_ptr<ASTExpressionNode> element);
    std::shared_ptr<ASTArrayNode> addComma(std::shared_ptr<ASTCommaNode> comma);
    void markElementsAsReferenced();
    std::shared_ptr<ASTLeftBracketNode> getLeftBracket();
    std::shared_ptr<ASTRightBracketNode> getRightBracket();
    std::optional<std::shared_ptr<ASTExpressionNode>> getFirstElement();
    std::vector<std::shared_ptr<ASTExpressionNode>>* getElements();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_NODE_H
