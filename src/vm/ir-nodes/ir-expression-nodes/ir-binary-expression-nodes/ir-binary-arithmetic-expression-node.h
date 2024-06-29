//
// Created by Johny Georges on 2024-06-29.
//

#ifndef JETLANG_IR_BINARY_ARITHMETIC_EXPRESSION_NODE_H
#define JETLANG_IR_BINARY_ARITHMETIC_EXPRESSION_NODE_H

#include <llvm/IR/InstrTypes.h>
#include "../../ir-node.h"
#include "../../../../core/ast/ast-nodes/ast-expression-nodes/ast-binary-expression-node.h"

class IRBinaryArithmeticExpressionNode : public IRNode {
private:
    ASTBinaryExpressionNode* _astNode;
    llvm::BinaryOperator* _irValue;
public:
    IRBinaryArithmeticExpressionNode(ASTBinaryExpressionNode* astBinaryExpressionNode, llvm::BinaryOperator* irValue);
    llvm::BinaryOperator* getIRValue();
    IRNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_IR_BINARY_ARITHMETIC_EXPRESSION_NODE_H
