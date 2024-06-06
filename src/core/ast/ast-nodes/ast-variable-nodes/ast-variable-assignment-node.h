//
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_AST_VARIABLE_ASSIGNMENT_NODE_H
#define JETLANG_AST_VARIABLE_ASSIGNMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "ast-variable-type-node.h"
#include "../ast-operator-nodes/ast-assignment-operator-node.h"

class ASTVariableAssignmentNode : public ASTNode {
private:
    ASTIdentifierNode* _identifier;
    ASTAssignmentOperatorNode* _assignmentOperator;
    TypeSignature* _typeSignature = new UnknownTypeSignature();
public:
    explicit ASTVariableAssignmentNode(ASTIdentifierNode* astIdentifierNode, ASTAssignmentOperatorNode* assignmentOperator);
    ASTIdentifierNode* getIdentifierNode();
    void setTypeSignature(TypeSignature* typeSignature);
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_VARIABLE_ASSIGNMENT_NODE_H
