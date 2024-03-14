//
// Created by Johny Georges on 2024-03-14.
//

#ifndef JETLANG_AST_BLOCK_DECLARATION_NODE_H
#define JETLANG_AST_BLOCK_DECLARATION_NODE_H

#include <vector>
#include "../ast-node.h"

class ASTBlockDeclarationNode : public ASTNode {
private:
    std::vector<ASTNode*> _contents;
public:
    explicit ASTBlockDeclarationNode();
    explicit ASTBlockDeclarationNode(std::vector<ASTNode*> contents);
    ASTBlockDeclarationNode* addContent(ASTNode* content);
    std::vector<ASTNode*> getContents();
    unsigned long size();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_BLOCK_DECLARATION_NODE_H
