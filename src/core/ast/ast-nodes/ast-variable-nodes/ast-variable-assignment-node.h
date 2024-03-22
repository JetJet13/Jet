//
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_AST_VARIABLE_ASSIGNMENT_NODE_H
#define JETLANG_AST_VARIABLE_ASSIGNMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "ast-variable-type-node.h"

class ASTVariableAssignmentNode : public ASTNode {
    ASTIdentifierNode* _identifier;
public:
    explicit ASTVariableAssignmentNode(ASTIdentifierNode* astIdentifierNode);
    ASTIdentifierNode* getIdentifierNode();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_VARIABLE_ASSIGNMENT_NODE_H
