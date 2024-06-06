//
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_AST_IF_BLOCK_NODE_H
#define JETLANG_AST_IF_BLOCK_NODE_H

#include "../ast-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "ast-control-flow-condition-node.h"
#include "ast-control-flow-block-node.h"
#include "ast-if-node.h"

class ASTIfBlockNode : public ASTScopedBlockNode {
private:
    ASTIfNode* _ifKeyword;
    ASTControlFlowConditionNode* _condition;
    ASTControlFlowBlockNode* _block;
public:
    explicit ASTIfBlockNode(ASTIfNode* ifKeyword, ASTControlFlowConditionNode* condition, ASTControlFlowBlockNode* block);
    ASTControlFlowBlockNode* getBlock();
    ASTControlFlowConditionNode* getCondition();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IF_BLOCK_NODE_H
