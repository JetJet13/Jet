//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_BINARY_ARITHMETIC_EXPRESSION_NODE_H
#define JETLANG_IR_BINARY_ARITHMETIC_EXPRESSION_NODE_H

#include <llvm/IR/InstrTypes.h>
#include "../../../../core/ast/ast-nodes/ast-expression-nodes/ast-binary-expression-node.h"
#include "ir-binary-expression-node.h"

class IRBinaryArithmeticExpressionNode : public IRBinaryExpressionNode {
private:
    ASTBinaryExpressionNode* _astNode;
    llvm::BinaryOperator* _irValue;
    IRExpressionNode* _irLeftNode;
    IRExpressionNode* _irRightNode;
public:
    IRBinaryArithmeticExpressionNode(ASTBinaryExpressionNode* astNode, llvm::BinaryOperator* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode);
    llvm::Value * insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) override;
    llvm::BinaryOperator* getIRValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_BINARY_ARITHMETIC_EXPRESSION_NODE_H
