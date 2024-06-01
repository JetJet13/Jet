//
// Created by Johny Georges on 2024-03-29.
//

#ifndef JETLANG_AST_WHILE_STATEMENT_NODE_H
#define JETLANG_AST_WHILE_STATEMENT_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-control-flow-nodes/ast-control-flow-condition-node.h"
#include "../ast-control-flow-nodes/ast-control-flow-block-node.h"
#include "ast-statement-node.h"
#include "../ast-control-flow-nodes/ast-while-node.h"

class ASTWhileStatementNode : public ASTStatementNode {
private:
    ASTWhileNode* _whileKeyword;
    ASTControlFlowConditionNode* _condition;
    ASTControlFlowBlockNode* _block;
public:
    explicit ASTWhileStatementNode(ASTWhileNode* whileKeyword, ASTControlFlowConditionNode* condition, ASTControlFlowBlockNode* block);
    ASTControlFlowBlockNode* getBlock();
    ASTControlFlowConditionNode* getCondition();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};


#endif //JETLANG_AST_WHILE_STATEMENT_NODE_H
