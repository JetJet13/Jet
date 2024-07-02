//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_UNARY_NEGATE_EXPRESSION_NODE_H
#define JETLANG_IR_UNARY_NEGATE_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/InstrTypes.h>
#include "../../../../core/ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"
#include "ir-unary-expression-node.h"

class IRUnaryNegateExpressionNode : public IRUnaryExpressionNode {
private:
    ASTUnaryExpressionNode* _astNode;
    llvm::UnaryOperator* _irValue;
public:
    IRUnaryNegateExpressionNode(ASTUnaryExpressionNode* astNode, llvm::UnaryOperator* irValue);
    llvm::UnaryOperator* getIRValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_IR_UNARY_NEGATE_EXPRESSION_NODE_H
