//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_CLASS_DECLARATION_NODE_H
#define JETLANG_AST_CLASS_DECLARATION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-class-nodes/ast-class-name-node.h"
#include "ast-class-property-declaration-node.h"
#include "../ast-class-nodes/ast-class-block-node.h"

class ASTClassDeclarationNode : public ASTDeclarationNode {
private:
    ASTClassNameNode* _name;
    ASTClassBlockNode* _block;
public:
    explicit ASTClassDeclarationNode(ASTClassNameNode* name, ASTClassBlockNode* block);
    ASTClassBlockNode* getBlock();
    ASTClassNameNode* getName();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_CLASS_DECLARATION_NODE_H
