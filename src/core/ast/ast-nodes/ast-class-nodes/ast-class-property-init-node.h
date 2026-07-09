//
// Created by Johny Georges on 2024-04-22.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_INIT_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_INIT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-type-node.h"
#include "../ast-variable-nodes/ast-variable-init-node.h"
#include "ast-class-property-name-node.h"
#include "../ast-access-modifier-nodes/ast-access-modifier-node.h"
#include "../ast-operator-nodes/ast-assignment-operator-node.h"
#include "ast-static-node.h"
#include "../ast-const-node.h"
#include "../ast-type-nodes/ast-type-colon-node.h"

class ASTClassPropertyInitNode : public ASTNode {
    std::shared_ptr<ASTAccessModifierNode> _accessModifier;
    std::shared_ptr<ASTClassPropertyNameNode> _propertyName;
    std::optional<std::shared_ptr<ASTAssignmentOperatorNode>> _assignmentOperator;
    std::optional<std::shared_ptr<ASTTypeColonNode>> _colon;
    std::optional<std::shared_ptr<ASTTypeNode>> _type;
    std::optional<std::shared_ptr<ASTStaticNode>> _staticKeyword;
    std::optional<std::shared_ptr<ASTConstNode>> _constKeyword;
public:
    explicit ASTClassPropertyInitNode(std::shared_ptr<ASTAccessModifierNode> accessModifier, std::shared_ptr<ASTClassPropertyNameNode> propertyName, std::optional<std::shared_ptr<ASTStaticNode>> staticKeyword = {}, std::optional<std::shared_ptr<ASTConstNode>> constKeyword = {}, std::optional<std::shared_ptr<ASTAssignmentOperatorNode>> assignmentOperator = {}, std::optional<std::shared_ptr<ASTTypeColonNode>> colon = {}, std::optional<std::shared_ptr<ASTTypeNode>> type = {});
    std::shared_ptr<ASTAccessModifierNode> getAccessModifier();
    std::shared_ptr<ASTClassPropertyNameNode> getPropertyName();
    std::optional<std::shared_ptr<ASTTypeNode>> getType();
    bool isStatic();
    bool isConstant();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_INIT_NODE_H
