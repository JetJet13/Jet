//
// Created by Johny Georges on 2025-01-08.
//

#ifndef JETLANG_IR_IF_ELSE_NODE_H
#define JETLANG_IR_IF_ELSE_NODE_H

#include "../../ir-expression-nodes/ir-expression-node.h"
#include "../../ir-block-node.h"

class IRIfElseNode : public IRNode {
private:
    IRExpressionNode* _condition;
    IRBlockNode* _thenBlock;
    IRBlockNode* _elseBlock;
public:
    IRIfElseNode(IRExpressionNode* condition, IRBlockNode* thenBlock, IRBlockNode* elseBlock);
    IRExpressionNode* getExpression();
    IRBlockNode* getThenBlock();
    IRBlockNode* getElseBlock();
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_IF_ELSE_NODE_H
