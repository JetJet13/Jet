//
// Created by Johny Georges on 2024-07-06.
//

#include "ir-array-access-expression-node.h"

IRArrayAccessExpressionNode::IRArrayAccessExpressionNode(ASTArrayAccessExpressionNode* astNode, IRExpressionNode* irSource, IRExpressionNode* irIndex) {
    _astNode = astNode;
    _irSource = irSource;
    _irIndex = irIndex;
}

llvm::Value * IRArrayAccessExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, llvm::Value *parent) {
    auto arrayElementType = _irSource->getIRTypeAtIndex(0);

    auto arrayAccessSourceAllocation = builder->get()->CreateAlloca(_irSource->getIRType());
    _irSource->insertSelfIntoBlock(builder, arrayAccessSourceAllocation);

    auto arrayAccessIndexAllocation = builder->get()->CreateAlloca(builder->get()->getInt32Ty());
    _irIndex->insertSelfIntoBlock(builder, arrayAccessIndexAllocation);
    auto index = builder->get()->CreateLoad(arrayElementType, arrayAccessIndexAllocation);

    auto zeroIndex = builder->get()->getInt32(0);
    auto sourcePointer = builder->get()->CreateInBoundsGEP(arrayAccessSourceAllocation->getAllocatedType(), arrayAccessSourceAllocation, { zeroIndex, index });
    auto valueAtIndex = builder->get()->CreateLoad(arrayElementType, sourcePointer);

    auto arrayAccessExpressionAllocation = builder->get()->CreateAlloca(arrayElementType);
    builder->get()->CreateStore(valueAtIndex, arrayAccessExpressionAllocation);
    builder->get()->CreateStore(valueAtIndex, parent);
    return arrayAccessExpressionAllocation;
}

llvm::Value* IRArrayAccessExpressionNode::getIRValue() {
    return _irSource->getIRValue();
}

IRNodeType IRArrayAccessExpressionNode::getNodeType() {
    return IR_ARRAY_ACCESS_EXPRESSION_NODE;
}

std::string IRArrayAccessExpressionNode::toString() {
    return "IR_ARRAY_ACCESS_EXPRESSION_NODE";
}

void IRArrayAccessExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irSource->print(stream);
    _irIndex->print(stream);
}