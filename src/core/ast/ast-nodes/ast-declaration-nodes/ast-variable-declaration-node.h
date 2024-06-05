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
private:
    ASTVariableInitNode* _varInit;
    ASTExpressionNode* _initializer;
    TypeSignature* _typeSignature = new UnknownTypeSignature();
public:
    explicit ASTVariableDeclarationNode(ASTVariableInitNode* varInit, ASTExpressionNode* initializer);
    ASTVariableInitNode* getVarInitNode();
    ASTExpressionNode* getInitializerNode();
    void setTypeSignature(TypeSignature* typeSignature);
    TypeSignature* getTypeSignature() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_VARIABLE_DECLARATION_NODE_H
