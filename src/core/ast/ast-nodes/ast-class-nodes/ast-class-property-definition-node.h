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
#include "ast-static-node.h"
#include "../ast-const-node.h"

class ASTClassPropertyDefinitionNode : public ASTNode {
protected:
    ASTAccessModifierNode* _accessModifier;
    ASTClassPropertyNameNode* _propertyName;
    std::optional<ASTStaticNode*> _staticKeyword;
    std::optional<ASTConstNode*> _constKeyword;
public:
    explicit ASTClassPropertyDefinitionNode(ASTAccessModifierNode* accessModifier, ASTClassPropertyNameNode* propertyName, std::optional<ASTStaticNode*> staticKeyword = {}, std::optional<ASTConstNode*> constKeyword = {});
    ASTAccessModifierNode* getAccessModifier();
    ASTClassPropertyNameNode* getPropertyName();
    std::optional<ASTStaticNode*> getStatic();
    std::optional<ASTConstNode*> getConstant();
    bool isStatic();
    bool isConstant();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_DEFINITION_NODE_H
