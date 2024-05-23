//
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_AST_ELSE_BLOCK_NODE_H
#define JETLANG_AST_ELSE_BLOCK_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "ast-control-flow-condition-node.h"
#include "ast-control-flow-block-node.h"

class ASTElseBlockNode : public ASTScopedBlockNode {
private:
    ASTControlFlowBlockNode* _block;
public:
    explicit ASTElseBlockNode(ASTControlFlowBlockNode* block);
    ASTControlFlowBlockNode* getBlock();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_ELSE_BLOCK_NODE_H
