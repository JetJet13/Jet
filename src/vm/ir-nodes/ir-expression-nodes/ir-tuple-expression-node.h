//
// Created by Johny Georges on 2024-07-01.
//

#ifndef JETLANG_IR_TUPLE_EXPRESSION_NODE_H
#define JETLANG_IR_TUPLE_EXPRESSION_NODE_H

#include <llvm/IR/Value.h>
#include <llvm/IR/Constants.h>
#include "../ir-node.h"
#include "../../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-expression-node.h"
#include "ir-expression-node.h"

class IRTupleExpressionNode : public IRExpressionNode {
private:
    ASTTupleExpressionNode* _astNode;
    llvm::Constant* _irValue;
public:
    IRTupleExpressionNode(ASTTupleExpressionNode* astNode, llvm::Constant* irValue);
    llvm::Constant* getConstantIRValue() override;
    llvm::Constant* getIRValue() override;
    IRNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_IR_TUPLE_EXPRESSION_NODE_H
