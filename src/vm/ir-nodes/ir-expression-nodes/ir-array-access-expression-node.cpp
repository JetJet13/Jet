//
// Created by Johny Georges on 2024-07-06.
//

#include "ir-array-access-expression-node.h"

IRArrayAccessExpressionNode::IRArrayAccessExpressionNode(ASTArrayAccessExpressionNode* node, IRExpressionNode* irSource, IRExpressionNode* irIndex, IRType* type) {
    _node = node;
    _irSource = irSource;
    _irIndex = irIndex;
    _type = type;
}

llvm::Value* IRArrayAccessExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    auto arrayElementType = _irSource->getTypeAtIndex(0);

    auto arrayAccessSourceAllocation = builder->get()->CreateAlloca(_irSource->getType());
    auto irSourceValue = _irSource->insertSelfIntoBlock(builder);
    builder->get()->CreateStore(irSourceValue, arrayAccessSourceAllocation);

    auto arrayAccessIndexAllocation = builder->get()->CreateAlloca(builder->get()->getInt32Ty());
    auto irIndexValue = _irIndex->insertSelfIntoBlock(builder);
    builder->get()->CreateStore(irIndexValue, arrayAccessIndexAllocation);
    auto index = builder->get()->CreateLoad(arrayElementType, arrayAccessIndexAllocation);

    auto zeroIndex = builder->get()->getInt32(0);
    auto sourcePointer = builder->get()->CreateInBoundsGEP(arrayAccessSourceAllocation->getAllocatedType(), arrayAccessSourceAllocation, { zeroIndex, index });

    return builder->get()->CreateLoad(arrayElementType, sourcePointer);
}

llvm::Value* IRArrayAccessExpressionNode::getValue() {
    return _irSource->getValue();
}

IRInstructionNode* IRArrayAccessExpressionNode::getSourceAllocation() {
    return _irSource->getSourceAllocation();
}

IRType* IRArrayAccessExpressionNode::getIRType() {
    return _type;
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