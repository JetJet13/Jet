//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-struct-expression-node.h"

IRStructExpressionNode::IRStructExpressionNode(ASTStructExpressionNode* astNode, llvm::AllocaInst* irAllocation, std::vector<IRExpressionNode*> irValues, llvm::GetElementPtrInst* irPointer) {
    _astNode = astNode;
    _irAllocation = irAllocation;
    _irValues = irValues;
    _irPointer = irPointer;
}

void IRStructExpressionNode::evaluate() {
    auto numElements =_irAllocation->getType()->getStructNumElements();
    for (int i = 0; i < numElements; ++i) {
        auto structElementType = _irAllocation->getType()->getStructElementType(i);
        auto irExpression = _irValues[i];
        irExpression->evaluate();
    }

}

llvm::AllocaInst* IRStructExpressionNode::getIRValue() {
    return _irAllocation;
}

IRNodeType IRStructExpressionNode::getNodeType() {
    return IR_STRUCT_EXPRESSION_NODE;
}

std::string IRStructExpressionNode::toString() {
    return "IR_STRUCT_EXPRESSION_NODE";
}