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
    std::shared_ptr<ASTUnaryExpressionNode> _node;
    llvm::BinaryOperator* _irValue;
    std::shared_ptr<IRExpressionNode> _irExpression;
    std::shared_ptr<IRType> _type;
public:
    IRUnaryArithmeticExpressionNode(std::shared_ptr<ASTUnaryExpressionNode> astNode, llvm::BinaryOperator* irValue, std::shared_ptr<IRExpressionNode> irExpression, std::shared_ptr<IRType> type);
    std::shared_ptr<IRExpressionNode> getIRValue();
    void markAsGlobal() override;
    llvm::BinaryOperator* getValue() override;
    std::shared_ptr<IRType> getIRType() override;
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
    void print(std::unique_ptr<llvm::raw_fd_ostream> *stream) override;
};

#endif //JETLANG_IR_UNARY_ARITHMETIC_EXPRESSION_NODE_H
