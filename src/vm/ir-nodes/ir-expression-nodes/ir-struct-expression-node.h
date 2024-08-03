//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_STRUCT_EXPRESSION_NODE_H
#define JETLANG_IR_STRUCT_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Instructions.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"
#include "ir-expression-node.h"
#include "../../ir-type/ir-struct-type.h"
#include "../ir-instruction-node.h"

class IRStructExpressionNode : public IRExpressionNode {
private:
    ASTStructExpressionNode* _astNode;
    IRInstructionNode* _irValue;
    std::vector<IRExpressionNode*> _irValues;
    IRPointerType* _type;
public:
    IRStructExpressionNode(ASTStructExpressionNode* astNode, IRInstructionNode* irValue, IRPointerType* type, std::vector<IRExpressionNode*> irValues);
    llvm::Value * insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    IRPointerType* getIRType() override;
    llvm::Value* getValue() override;
    IRInstructionNode* getSourceAllocation() override;
    IRInstructionNode* getSourceAllocationAtIndex(unsigned long index) override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_STRUCT_EXPRESSION_NODE_H
