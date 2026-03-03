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
    ASTUnaryExpressionNode* _node;
    llvm::BinaryOperator* _irValue;
    IRExpressionNode* _irExpression;
    IRType* _type;
public:
    IRUnaryArithmeticExpressionNode(ASTUnaryExpressionNode* astNode, llvm::BinaryOperator* irValue, IRExpressionNode* irExpression, IRType* type);
    IRExpressionNode* getIRValue();
    void markAsGlobal() override;
    llvm::BinaryOperator* getValue() override;
    IRType* getIRType() override;
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_UNARY_ARITHMETIC_EXPRESSION_NODE_H
