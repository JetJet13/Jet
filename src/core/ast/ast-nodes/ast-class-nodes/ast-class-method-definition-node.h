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
// Created by Johny Georges on 2024-04-26.
//

#ifndef JETLANG_AST_CLASS_METHOD_DEFINITION_NODE_H
#define JETLANG_AST_CLASS_METHOD_DEFINITION_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-type-node.h"
#include "../ast-variable-nodes/ast-variable-init-node.h"
#include "ast-class-property-name-node.h"
#include "../ast-access-modifier-nodes/ast-access-modifier-node.h"
#include "ast-class-method-name-node.h"
#include "ast-static-node.h"

class ASTClassMethodDefinitionNode : public ASTNode {
protected:
    std::shared_ptr<ASTAccessModifierNode> _accessModifier;
    std::shared_ptr<ASTClassMethodNameNode> _methodName;
    std::optional<std::shared_ptr<ASTStaticNode>> _staticKeyword;
public:
    explicit ASTClassMethodDefinitionNode(std::shared_ptr<ASTAccessModifierNode> accessModifier, std::shared_ptr<ASTClassMethodNameNode> methodName, std::optional<std::shared_ptr<ASTStaticNode>> staticKeyword = {});
    std::shared_ptr<ASTAccessModifierNode> getAccessModifier();
    std::shared_ptr<ASTClassMethodNameNode> getMethodName();
    bool isStatic();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_METHOD_DEFINITION_NODE_H
