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
// Created by Johny Georges on 2024-03-09.
//

#ifndef JETLANG_AST_ARRAY_EXPRESSION_NODE_H
#define JETLANG_AST_ARRAY_EXPRESSION_NODE_H

#include <vector>
#include <string>
#include "../ast-node.h"
#include "ast-expression-node.h"
#include "../../../type-signature/array-type-signature/array-type-signature.h"
#include "../ast-array-nodes/ast-array-node.h"

class ASTArrayExpressionNode : public ASTExpressionNode {
private:
    std::shared_ptr<ASTArrayNode> _array;
    std::shared_ptr<ArrayTypeSignature> _typeSignature = std::make_shared<ArrayTypeSignature>();
public:
    explicit ASTArrayExpressionNode(std::shared_ptr<ASTArrayNode> array);
    std::shared_ptr<ASTArrayNode> getArray();
    std::vector<std::shared_ptr<ASTExpressionNode>>* getElements();
    std::shared_ptr<ASTArrayExpressionNode> addElement(std::shared_ptr<ASTExpressionNode> element);
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<ArrayTypeSignature> getArrayTypeSignature();
    void setTypeSignature(std::shared_ptr<ArrayTypeSignature> arrayTypeSignature);
    uint64_t size();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_EXPRESSION_NODE_H
