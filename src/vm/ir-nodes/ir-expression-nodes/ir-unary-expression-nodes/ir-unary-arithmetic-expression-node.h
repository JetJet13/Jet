//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_UNARY_ARITHMETIC_EXPRESSION_NODE_H
#define JETLANG_IR_UNARY_ARITHMETIC_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/InstrTypes.h>
#include "../../../../core/ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"
#include "ir-unary-expression-node.h"

class IRUnaryArithmeticExpressionNode : public IRUnaryExpressionNode {
private:
    ASTUnaryExpressionNode* _astNode;
    llvm::BinaryOperator* _irValue;
    IRExpressionNode* _irExpression;
    IRPointerType* _type;
    IRInstructionNode* _sourceAllocation;
public:
    IRUnaryArithmeticExpressionNode(ASTUnaryExpressionNode* astNode, llvm::BinaryOperator* irValue, IRExpressionNode* irExpression, IRPointerType* type, IRInstructionNode* sourceAllocation);
    llvm::Value * insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::BinaryOperator* getValue() override;
    IRInstructionNode* getSourceAllocation() override;
    IRPointerType* getIRType() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_UNARY_ARITHMETIC_EXPRESSION_NODE_H
