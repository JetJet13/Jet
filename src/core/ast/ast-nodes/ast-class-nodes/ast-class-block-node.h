//
// Created by Johny Georges on 2024-04-19.
//

#ifndef JETLANG_AST_CLASS_BLOCK_NODE_H
#define JETLANG_AST_CLASS_BLOCK_NODE_H

#include "../ast-node.h"

class ASTClassBlockNode : public ASTNode {
private:
    std::vector<ASTNode*> _contents;
public:
    explicit ASTClassBlockNode(std::vector<ASTNode*> contents);
    std::vector<ASTNode*> getContents();
    ASTNodeType getNodeType() override;
    bool isSameAs(ASTNode* other) override;
    std::string toString() override;
    void print() override;
};

#endif //JETLANG_AST_CLASS_BLOCK_NODE_H
