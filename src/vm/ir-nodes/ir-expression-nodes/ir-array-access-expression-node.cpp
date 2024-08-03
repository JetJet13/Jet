//
// Created by Johny Georges on 2024-07-06.
//

#include "ir-array-access-expression-node.h"

IRArrayAccessExpressionNode::IRArrayAccessExpressionNode(ASTArrayAccessExpressionNode* node, IRExpressionNode* irSource, IRExpressionNode* irIndex, IRPointerType* type) {
    _node = node;
    _irSource = irSource;
    _irIndex = irIndex;
    _type = type;
}

llvm::Value* IRArrayAccessExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {

    auto irSourceValue = _irSource->insertSelfIntoBlock(builder);
    auto irIndexValue = _irIndex->insertSelfIntoBlock(builder);
    auto zeroIndex = builder->get()->getInt32(0);
    auto sourcePointer = builder->get()->CreateInBoundsGEP(irSourceValue->getType(), irSourceValue, { zeroIndex, irIndexValue });
//  make every element of an array a pointer that points to the source allocation, regardless
//  of source allocation type. llvm pointers can have types (see llvm::PointerType::get())

    return builder->get()->CreateLoad(sourcePointer->getType(), sourcePointer);
}

llvm::Value* IRArrayAccessExpressionNode::getValue() {
    return _irSource->getValue();
}

IRInstructionNode* IRArrayAccessExpressionNode::getSourceAllocation() {
    return _irSource->getSourceAllocation();
}

IRPointerType* IRArrayAccessExpressionNode::getIRType() {
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