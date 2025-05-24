//
// Created by Johny Georges on 2025-05-24.
//

#ifndef JETLANG_IR_WHILE_STATEMENT_NODE_H
#define JETLANG_IR_WHILE_STATEMENT_NODE_H

#include "../ir-statement-node.h"
#include "../../../../core/ast/ast-nodes/ast-statement-nodes/ast-while-statement-node.h"
#include "../../ir-block-node.h"

class IRWhileStatementNode : public IRStatementNode {
private:
    ASTWhileStatementNode* _node;
    IRExpressionNode* _condition;
    IRBlockNode* _whileBlock;
    IRBlockNode* _bodyBlock;
    IRBlockNode* _endBlock;
public:
    IRWhileStatementNode(ASTWhileStatementNode* node, IRExpressionNode* condition, IRBlockNode* whileBlock, IRBlockNode* bodyBlock, IRBlockNode* endBlock);
    IRExpressionNode* getExpression();
    IRBlockNode* getWhileBlock();
    IRBlockNode* getBodyBlock();
    IRBlockNode* getEndBlock();
    void setBlocksToBeSuccessorsOf(IRBlockNode* irBlock);
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_WHILE_STATEMENT_NODE_H
