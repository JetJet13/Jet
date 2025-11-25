//
// Created by Johny Georges on 2025-01-08.
//

#ifndef JETLANG_IR_IF_ELSE_NODE_H
#define JETLANG_IR_IF_ELSE_NODE_H

#include "../../ir-expression-nodes/ir-expression-node.h"
#include "../../ir-block-nodes/ir-block-node.h"

class IRIfElseNode : public IRNode {
private:
    IRExpressionNode* _condition;
    IRBlockNode* _ifBlock;
    IRBlockNode* _thenBlock;
    IRBlockNode* _elseBlock;
    IRBlockNode* _endBlock;
    std::optional<IRIfElseNode*> _next;
public:
    IRIfElseNode(IRExpressionNode* condition, IRBlockNode* ifBlock, IRBlockNode* thenBlock, IRBlockNode* elseBlock, IRBlockNode* endBlock, std::optional<IRIfElseNode*> next = {});
    IRExpressionNode* getExpression();
    IRBlockNode* getIfBlock();
    IRBlockNode* getThenBlock();
    IRBlockNode* getElseBlock();
    IRBlockNode* getEndBlock();
    void setBlocksToBeSuccessorsOf(IRBlockNode* irBlock);
    void setNext(IRIfElseNode* next);
    std::optional<IRIfElseNode*> getNext();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_IF_ELSE_NODE_H
