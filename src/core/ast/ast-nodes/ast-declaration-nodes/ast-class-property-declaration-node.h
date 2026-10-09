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
// Created by Johny Georges on 2024-04-19.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_DECLARATION_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_DECLARATION_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-type-node.h"
#include "../ast-variable-nodes/ast-variable-init-node.h"
#include "../ast-class-nodes/ast-class-property-name-node.h"
#include "../ast-access-modifier-nodes/ast-access-modifier-node.h"
#include "../ast-class-nodes/ast-class-property-init-node.h"
#include "ast-declaration-node.h"
#include "../../../type-signature/class-type-signature/class-property-type-signature/class-property-type-signature.h"

class ASTClassPropertyDeclarationNode : public ASTDeclarationNode {
private:
    std::shared_ptr<ASTClassPropertyInitNode> _propertyInit;
    std::optional<std::shared_ptr<ASTExpressionNode>> _initializer;
    std::string _normalizedPropertyName;
    std::shared_ptr<ClassPropertyTypeSignature> _typeSignature = std::make_shared<ClassPropertyTypeSignature>();
public:
    explicit ASTClassPropertyDeclarationNode(std::shared_ptr<ASTClassPropertyInitNode> propertyInit, std::optional<std::shared_ptr<ASTExpressionNode>> initializer = {});
    std::shared_ptr<ASTClassPropertyInitNode> getPropertyInit();
    std::shared_ptr<ASTAccessModifierNode> getAccessModifier();
    std::shared_ptr<ASTClassPropertyNameNode> getPropertyName();
    std::string getNormalizedPropertyName();
    std::optional<std::shared_ptr<ASTTypeNode>> getType();
    std::optional<std::shared_ptr<ASTExpressionNode>> getInitializer();
    bool isPublic();
    bool isPrivate();
    bool isStatic();
    bool isConstant();
    void setTypeSignature(std::shared_ptr<ClassPropertyTypeSignature> typeSignature);
    std::shared_ptr<ClassPropertyTypeSignature> getPropertyTypeSignature();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_DECLARATION_NODE_H
