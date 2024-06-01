//
// Created by Johny Georges on 2024-04-01.
//

#ifndef JETLANG_AST_TRY_BLOCK_NODE_H
#define JETLANG_AST_TRY_BLOCK_NODE_H

#include "../../ast-node.h"
#include "../../ast-type-nodes/ast-type-node.h"
#include "../ast-control-flow-condition-node.h"
#include "../ast-control-flow-block-node.h"
#include "ast-try-node.h"

class ASTTryBlockNode : public ASTScopedBlockNode {
private:
    ASTTryNode* _tryKeyword;
    ASTControlFlowBlockNode* _block;
public:
    explicit ASTTryBlockNode(ASTTryNode* tryKeyword, ASTControlFlowBlockNode* block);
    ASTControlFlowBlockNode* getBlock();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TRY_BLOCK_NODE_H
