//
// Created by Johny Georges on 2024-03-29.
//

#ifndef JETLANG_AST_WHILE_STATEMENT_NODE_H
#define JETLANG_AST_WHILE_STATEMENT_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-type-node.h"
#include "../ast-control-flow-nodes/ast-control-flow-condition-node.h"
#include "../ast-control-flow-nodes/ast-control-flow-block-node.h"

class ASTWhileStatementNode : public ASTNode {
private:
    ASTControlFlowConditionNode* _condition;
    ASTControlFlowBlockNode* _block;
public:
    explicit ASTWhileStatementNode(ASTControlFlowConditionNode* condition, ASTControlFlowBlockNode* block);
    ASTControlFlowBlockNode* getBlock();
    ASTControlFlowConditionNode* getCondition();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};


#endif //JETLANG_AST_WHILE_STATEMENT_NODE_H
