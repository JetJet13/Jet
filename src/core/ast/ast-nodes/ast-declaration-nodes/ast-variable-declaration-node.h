//
// Created by Johny Georges on 2024-01-12.
//

#ifndef JETLANG_AST_VARIABLE_DECLARATION_NODE_H
#define JETLANG_AST_VARIABLE_DECLARATION_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-type-node.h"
#include "../ast-variable-nodes/ast-variable-init-node.h"
#include "ast-declaration-node.h"

class ASTVariableDeclarationNode : public ASTDeclarationNode {
    ASTVariableInitNode* _varInit;
    ASTExpressionNode* _initializer;
public:
    explicit ASTVariableDeclarationNode(ASTVariableInitNode* varInit, ASTExpressionNode* initializer);
    ASTVariableInitNode* getVarInitNode();
    ASTExpressionNode* getInitializerNode();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_VARIABLE_DECLARATION_NODE_H
