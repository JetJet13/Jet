//
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_AST_ELSE_IF_BLOCK_NODE_H
#define JETLANG_AST_ELSE_IF_BLOCK_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "ast-control-flow-condition-node.h"
#include "ast-control-flow-block-node.h"
#include "ast-else-if-node.h"

class ASTElseIfBlockNode : public ASTScopedBlockNode {
private:
    ASTElseIfNode* _elseIfKeyword;
    ASTControlFlowConditionNode* _condition;
    ASTControlFlowBlockNode* _block;
public:
    explicit ASTElseIfBlockNode(ASTElseIfNode* elseIfKeyword, ASTControlFlowConditionNode* condition, ASTControlFlowBlockNode* block);
    ASTControlFlowBlockNode* getBlock();
    ASTControlFlowConditionNode* getCondition();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ELSE_IF_BLOCK_NODE_H
