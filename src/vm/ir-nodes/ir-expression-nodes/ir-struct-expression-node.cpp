//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-struct-expression-node.h"

IRStructExpressionNode::IRStructExpressionNode(ASTStructExpressionNode* astNode, llvm::AllocaInst* irAllocation, std::vector<IRExpressionNode*> irValues, llvm::GetElementPtrInst* irPointer) {
    _astNode = astNode;
    _irAllocation = irAllocation;
    _irValues = irValues;
    _irPointer = irPointer;
    _irStatements = std::vector<llvm::Value*>();
    this->generateStatements();
}

llvm::Value * IRStructExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, llvm::Value *parent) {
    auto structExpressionAllocation = builder->get()->Insert(_irAllocation);
    auto numElements = _irValues.size();
    auto zeroIndex = builder->get()->getInt32(0);
    for (int i = 0; i < numElements; ++i) {
        auto irExpression = _irValues[i];
        auto irIndex = builder->get()->getInt32(i);
        auto pointer = builder->get()->CreateInBoundsGEP(structExpressionAllocation->getAllocatedType(), structExpressionAllocation, { zeroIndex, irIndex });
        irExpression->insertSelfIntoBlock(builder, pointer);
    }
    builder->get()->CreateStore(structExpressionAllocation, parent);
    return structExpressionAllocation;
}

llvm::Constant* IRStructExpressionNode::getIRValue() {

}

IRNodeType IRStructExpressionNode::getNodeType() {
    return IR_STRUCT_EXPRESSION_NODE;
}

std::string IRStructExpressionNode::toString() {
    return "IR_STRUCT_EXPRESSION_NODE";
}

void IRStructExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    for (auto irStatement : _irStatements) {
        irStatement->print(**stream);
        stream->get()->write('\n');
    }
}

void IRStructExpressionNode::generateStatements() {
    _irStatements.push_back(_irAllocation);
    _irStatements.push_back(_irPointer);
    auto numElements = _irValues.size();
    for (int i = 0; i < numElements; ++i) {
        auto irExpression = _irValues[i];
        _irStatements.push_back(irExpression->getIRValue());
        _irStatements.push_back(
            new llvm::StoreInst(irExpression->getIRValue(), _irPointer, false, _irAllocation->getAlign())
        );
    }
}