//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_TUPLE_EXPRESSION_NODE_H
#define JETLANG_IR_TUPLE_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include "../ir-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-expression-node.h"
#include "ir-constant-expression-node.h"

class IRTupleExpressionNode : public IRConstantExpressionNode {
private:
    ASTTupleExpressionNode* _node;
    llvm::Constant* _irValue;
    std::vector<IRExpressionNode*> _irValues;
public:
    IRTupleExpressionNode(ASTTupleExpressionNode* node, llvm::Constant* irValue, std::vector<IRExpressionNode*> irValues);
    llvm::Value * insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::Constant* getIRValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_TUPLE_EXPRESSION_NODE_H
