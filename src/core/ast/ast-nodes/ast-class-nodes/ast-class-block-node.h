//
// Created by Johny Georges on 2024-04-19.
//

#ifndef JETLANG_AST_CLASS_BLOCK_NODE_H
#define JETLANG_AST_CLASS_BLOCK_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-expression-nodes/ast-function-return-expression-node.h"
#include "../ast-declaration-nodes/ast-class-method-declaration-node.h"

class ASTClassBlockNode : public ASTNode {
private:
    std::vector<ASTClassPropertyDeclarationNode*> _properties;
    std::vector<ASTClassMethodDeclarationNode*> _methods;
public:
    explicit ASTClassBlockNode(std::vector<ASTNode*> contents);
    std::vector<ASTNode*> getContents();
    ASTNodeType getNodeType() override;
    bool isSameAs(ASTNode* other) override;
    std::string toString() override;
    void print() override;
};

#endif //JETLANG_AST_CLASS_BLOCK_NODE_H
