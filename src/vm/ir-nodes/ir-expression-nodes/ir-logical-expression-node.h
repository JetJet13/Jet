//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_LOGICAL_EXPRESSION_NODE_H
#define JETLANG_IR_LOGICAL_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/InstrTypes.h>
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-logical-expression-node.h"
#include "ir-expression-node.h"

class IRLogicalExpressionNode : public IRExpressionNode {
private:
    ASTLogicalExpressionNode* _astNode;
    llvm::BinaryOperator* _irValue;
    IRExpressionNode* _irLeftNode;
    IRExpressionNode* _irRightNode;
    IRPointerType* _type;
    IRInstructionNode* _sourceAllocation;
public:
    IRLogicalExpressionNode(ASTLogicalExpressionNode* astNode, llvm::BinaryOperator* irValue, IRPointerType* type, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode, IRInstructionNode* sourceAllocation);
    llvm::Value * insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    IRPointerType* getIRType() override;
    llvm::BinaryOperator* getValue() override;
    IRInstructionNode* getSourceAllocation() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_LOGICAL_EXPRESSION_NODE_H
