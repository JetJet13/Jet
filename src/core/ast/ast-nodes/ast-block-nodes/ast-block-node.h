//
// Created by Johny Georges on 2024-03-14.
//

#ifndef JETLANG_AST_BLOCK_NODE_H
#define JETLANG_AST_BLOCK_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"

class ASTBlockNode : public ASTNode {
private:
    std::vector<ASTNode*> _contents;
public:
    explicit ASTBlockNode();
    explicit ASTBlockNode(std::vector<ASTNode*> contents);
    ASTBlockNode* addContent(ASTNode* content);
    unsigned long size();
    std::vector<ASTNode*> getContents();
    ASTNode* transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, HandleMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    void print() override;
};

#endif //JETLANG_AST_BLOCK_NODE_H
