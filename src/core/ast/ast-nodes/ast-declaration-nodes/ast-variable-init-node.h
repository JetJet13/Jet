//
// Created by Johny Georges on 2024-02-08.
//

#ifndef JETLANG_AST_VARIABLE_INIT_NODE_H
#define JETLANG_AST_VARIABLE_INIT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "ast-variable-type-node.h"

class ASTVariableInitNode : public ASTNode {
    ASTVariableTypeNode* _assignmentTypeQualifier;
    ASTIdentifierNode* _identifier;
public:
    explicit ASTVariableInitNode(ASTVariableTypeNode* assignmentTypeQualifier, ASTIdentifierNode* astIdentifierNode);
    void setIdentifier(ASTIdentifierNode* astIdentifierNode);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isEqual(ASTNode* other) override;
};

#endif //JETLANG_AST_VARIABLE_INIT_NODE_H
