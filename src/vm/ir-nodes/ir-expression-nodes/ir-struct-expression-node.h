//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_STRUCT_EXPRESSION_NODE_H
#define JETLANG_IR_STRUCT_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Instructions.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"
#include "ir-expression-node.h"
#include "ir-constant-expression-node.h"

class IRStructExpressionNode : public IRConstantExpressionNode {
private:
    ASTStructExpressionNode* _astNode;
    llvm::Constant* _irValue;
    std::vector<IRExpressionNode*> _irValues;
public:
    IRStructExpressionNode(ASTStructExpressionNode* astNode, llvm::Constant* irValue, std::vector<IRExpressionNode*> irValues);
    llvm::Value * insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, llvm::Value *parent) override;
    llvm::Constant* getIRValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_STRUCT_EXPRESSION_NODE_H
