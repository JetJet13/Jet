//
// Created by Johny Georges on 2024-01-12.
//

#ifndef JETLANG_AST_VARIABLE_DECLARATION_NODE_H
#define JETLANG_AST_VARIABLE_DECLARATION_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "ast-variable-type-node.h"
#include "ast-variable-init-node.h"

class ASTVariableDeclarationNode : public ASTNode {
    ASTVariableInitNode* _varInit;
    ASTExpressionNode* _initializer;
public:
    explicit ASTVariableDeclarationNode(ASTVariableInitNode* varInit, ASTExpressionNode* initializer);
    ASTNodeType getNodeType() override;
};

#endif //JETLANG_AST_VARIABLE_DECLARATION_NODE_H
