//
// Created by Johny Georges on 2024-02-08.
//

#ifndef JETLANG_AST_VARIABLE_INIT_NODE_H
#define JETLANG_AST_VARIABLE_INIT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "ast-variable-type-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-base-nodes/ast-colon-base-node.h"
#include "../ast-operator-nodes/ast-assignment-operator-node.h"
#include "../ast-type-nodes/ast-type-colon-node.h"

class ASTVariableInitNode : public ASTNode {
    std::shared_ptr<ASTVariableTypeNode> _assignmentTypeQualifier;
    std::shared_ptr<ASTIdentifierNode> _identifier;
    std::optional<std::shared_ptr<ASTTypeColonNode>> _colon;
    std::optional<std::shared_ptr<ASTTypeNode>> _type;
    std::shared_ptr<ASTAssignmentOperatorNode> _assignmentOperator;
public:
    explicit ASTVariableInitNode(std::shared_ptr<ASTVariableTypeNode> assignmentTypeQualifier, std::shared_ptr<ASTIdentifierNode> astIdentifierNode, std::shared_ptr<ASTAssignmentOperatorNode> assignmentOperator, std::optional<std::shared_ptr<ASTTypeColonNode>> colon = {}, std::optional<std::shared_ptr<ASTTypeNode>> type = {});
    std::shared_ptr<ASTVariableTypeNode> getVarTypeNode();
    std::shared_ptr<ASTIdentifierNode> getIdentifierNode();
    std::optional<std::shared_ptr<ASTTypeNode>> getTypeNode();
    bool isConst();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_VARIABLE_INIT_NODE_H
