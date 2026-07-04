//
// Created by Johny Georges on 2026-02-16.
//

#ifndef JETLANG_AST_REF_VALUE_ASSIGNMENT_NODE_H
#define JETLANG_AST_REF_VALUE_ASSIGNMENT_NODE_H

#include "ast-node.h"
#include "ast-expression-nodes/ast-expression-node.h"
#include "ast-identifier-node.h"
#include "ast-variable-nodes/ast-variable-type-node.h"
#include "ast-operator-nodes/ast-assignment-operator-node.h"
#include "ast-operator-nodes/ast-ref-value-assignment-operator-node.h"

class ASTRefValueAssignmentNode : public ASTNode {
private:
    std::shared_ptr<ASTIdentifierNode> _identifier;
    std::shared_ptr<ASTRefValueAssignmentOperatorNode> _assignmentOperator;
    TypeSignature* _typeSignature = new UnknownTypeSignature();
public:
    explicit ASTRefValueAssignmentNode(std::shared_ptr<ASTIdentifierNode> astIdentifierNode, std::shared_ptr<ASTRefValueAssignmentOperatorNode> assignmentOperator);
    std::shared_ptr<ASTIdentifierNode> getIdentifierNode();
    void setTypeSignature(TypeSignature* typeSignature);
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_REF_VALUE_ASSIGNMENT_NODE_H
