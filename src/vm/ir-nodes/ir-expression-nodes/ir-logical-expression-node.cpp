//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-logical-expression-node.h"

IRLogicalExpressionNode::IRLogicalExpressionNode(ASTLogicalExpressionNode* astNode, llvm::BinaryOperator* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode) {
    _astNode = astNode;
    _irValue = irValue;
    _irLeftNode = irLeftNode;
    _irRightNode = irRightNode;
}

llvm::Value * IRLogicalExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, llvm::Value *parent) {
    auto leftNodeAllocation = builder->get()->CreateAlloca(_irLeftNode->getIRType());
    _irLeftNode->insertSelfIntoBlock(builder, leftNodeAllocation);
    auto leftNodeValue = builder->get()->CreateLoad(leftNodeAllocation->getAllocatedType(), leftNodeAllocation);

    auto rightNodeAllocation = builder->get()->CreateAlloca(_irRightNode->getIRType());
    _irRightNode->insertSelfIntoBlock(builder, rightNodeAllocation);
    auto rightNodeValue = builder->get()->CreateLoad(rightNodeAllocation->getAllocatedType(), rightNodeAllocation);

    auto logicalResult = builder->get()->CreateBinOp(_irValue->getOpcode(), leftNodeValue, rightNodeValue);

    return builder->get()->CreateStore(logicalResult, parent);
}

llvm::BinaryOperator* IRLogicalExpressionNode::getIRValue() {
    return _irValue;
}

IRNodeType IRLogicalExpressionNode::getNodeType() {
    return IR_LOGICAL_EXPRESSION_NODE;
}

std::string IRLogicalExpressionNode::toString() {
    return "IR_LOGICAL_EXPRESSION_NODE";
}

void IRLogicalExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
    stream->get()->write('\n');
    _irLeftNode->print(stream);
    stream->get()->write('\n');
    _irRightNode->print(stream);
}