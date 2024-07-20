//
// Created by Johny Georges on 2024-07-06.
//

#ifndef JETLANG_IR_ARRAY_ACCESS_EXPRESSION_NODE_H
#define JETLANG_IR_ARRAY_ACCESS_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-array-access-expression-node.h"
#include "ir-expression-node.h"


class IRArrayAccessExpressionNode : public IRExpressionNode {
private:
    ASTArrayAccessExpressionNode* _node;
    IRExpressionNode* _irSource;
    IRExpressionNode* _irIndex;
public:
    IRArrayAccessExpressionNode(ASTArrayAccessExpressionNode* node, IRExpressionNode* irSource, IRExpressionNode* irIndex);
    llvm::Value * insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::Value* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_ARRAY_ACCESS_EXPRESSION_NODE_H
