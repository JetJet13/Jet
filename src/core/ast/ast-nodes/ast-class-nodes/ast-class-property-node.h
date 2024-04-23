//
// Created by Johny Georges on 2024-04-19.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-type-node.h"
#include "../ast-variable-nodes/ast-variable-init-node.h"
#include "ast-class-property-name-node.h"
#include "../ast-access-modifier-nodes/ast-access-modifier-node.h"
#include "ast-class-property-init-node.h"

class ASTClassPropertyNode : public ASTNode {
    ASTClassPropertyInitNode* _propertyInit;
    std::optional<ASTExpressionNode*> _initializer;
public:
    explicit ASTClassPropertyNode(ASTClassPropertyInitNode* propertyInit, std::optional<ASTExpressionNode*> initializer = {});
    ASTClassPropertyInitNode* getPropertyInit();
    ASTAccessModifierNode* getAccessModifier();
    ASTClassPropertyNameNode* getPropertyName();
    std::optional<ASTTypeNode*> getType();
    std::optional<ASTExpressionNode*> getInitializer();
    bool isStatic();
    bool isConstant();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_NODE_H
