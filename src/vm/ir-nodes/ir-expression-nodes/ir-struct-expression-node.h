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
#include "../../ir-type/ir-struct-type.h"

class IRStructExpressionNode : public IRConstantExpressionNode {
private:
    ASTStructExpressionNode* _astNode;
    llvm::Constant* _irValue;
    std::vector<IRExpressionNode*> _irValues;
    IRStructType* _type;
public:
    IRStructExpressionNode(ASTStructExpressionNode* astNode, llvm::Constant* irValue, IRStructType* type, std::vector<IRExpressionNode*> irValues);
    llvm::Value * insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    IRStructType* getIRType() override;
    llvm::Constant* getValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_STRUCT_EXPRESSION_NODE_H
