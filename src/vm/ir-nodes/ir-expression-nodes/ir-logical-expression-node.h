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
public:
    IRLogicalExpressionNode(ASTLogicalExpressionNode* astNode, llvm::BinaryOperator* irValue);
    llvm::BinaryOperator* getIRValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_IR_LOGICAL_EXPRESSION_NODE_H
