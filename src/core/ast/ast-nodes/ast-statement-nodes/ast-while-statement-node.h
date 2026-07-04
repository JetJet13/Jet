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
    std::shared_ptr<ASTWhileNode> _whileKeyword;
    std::shared_ptr<ASTControlFlowConditionNode> _condition;
    std::shared_ptr<ASTControlFlowBlockNode> _block;
public:
    explicit ASTWhileStatementNode(std::shared_ptr<ASTWhileNode> whileKeyword, std::shared_ptr<ASTControlFlowConditionNode> condition, std::shared_ptr<ASTControlFlowBlockNode> block);
    std::shared_ptr<ASTControlFlowBlockNode> getBlock();
    std::shared_ptr<ASTControlFlowConditionNode> getCondition();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};


#endif //JETLANG_AST_WHILE_STATEMENT_NODE_H
