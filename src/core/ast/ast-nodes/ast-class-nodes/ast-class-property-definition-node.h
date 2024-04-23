//
// Created by Johny Georges on 2024-04-22.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_DEFINITION_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_DEFINITION_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-type-node.h"
#include "../ast-variable-nodes/ast-variable-init-node.h"
#include "ast-class-property-name-node.h"
#include "../ast-access-modifier-nodes/ast-access-modifier-node.h"

class ASTClassPropertyDefinitionNode : public ASTNode {
    ASTAccessModifierNode* _accessModifier;
    ASTClassPropertyNameNode* _propertyName;
    bool _isStatic;
    bool _isConstant;
public:
    explicit ASTClassPropertyDefinitionNode(ASTAccessModifierNode* accessModifier, ASTClassPropertyNameNode* propertyName, bool isStatic, bool isConstant);
    ASTAccessModifierNode* getAccessModifier();
    ASTClassPropertyNameNode* getPropertyName();
    bool isStatic();
    bool isConstant();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_DEFINITION_NODE_H
