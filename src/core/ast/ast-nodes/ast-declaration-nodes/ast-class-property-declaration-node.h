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

class ASTClassPropertyDeclarationNode : public ASTNode {
    ASTAccessModifierNode* _accessModifier;
    ASTClassPropertyNameNode* _propertyName;
    std::optional<ASTTypeNode*> _type;
    std::optional<ASTExpressionNode*> _initializer;
    bool _isStatic;
    bool _isConstant;
public:
    explicit ASTClassPropertyDeclarationNode(ASTAccessModifierNode* accessModifier, ASTClassPropertyNameNode* propertyName, bool isStatic, bool isConstant, std::optional<ASTTypeNode*> type = {}, std::optional<ASTExpressionNode*> initializer = {});
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

#endif //JETLANG_AST_CLASS_PROPERTY_DECLARATION_NODE_H
