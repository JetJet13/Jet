//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-binary-arithmetic-expression-node.h"

IRBinaryArithmeticExpressionNode::IRBinaryArithmeticExpressionNode(ASTBinaryExpressionNode* astNode, llvm::BinaryOperator* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode) {
    _astNode = astNode;
    _irValue = irValue;
    _irLeftNode = irLeftNode;
    _irRightNode = irRightNode;
}

llvm::Value * IRBinaryArithmeticExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, llvm::Value *parent) {
    auto leftNodeAllocation = builder->get()->CreateAlloca(_irLeftNode->getIRType());
    _irLeftNode->insertSelfIntoBlock(builder, leftNodeAllocation);
    auto leftNodeValue = builder->get()->CreateLoad(leftNodeAllocation->getAllocatedType(), leftNodeAllocation);

    auto rightNodeAllocation = builder->get()->CreateAlloca(_irRightNode->getIRType());
    _irRightNode->insertSelfIntoBlock(builder, rightNodeAllocation);
    auto rightNodeValue = builder->get()->CreateLoad(rightNodeAllocation->getAllocatedType(), rightNodeAllocation);

    auto binaryResult = builder->get()->CreateBinOp(_irValue->getOpcode(), leftNodeValue, rightNodeValue);

    return builder->get()->CreateStore(binaryResult, parent);
}

llvm::BinaryOperator* IRBinaryArithmeticExpressionNode::getIRValue() {
    return _irValue;
}

IRNodeType IRBinaryArithmeticExpressionNode::getNodeType() {
    return IR_BINARY_ARITHMETIC_EXPRESSION_NODE;
}

std::string IRBinaryArithmeticExpressionNode::toString() {
    return "IR_BINARY_ARITHMETIC_EXPRESSION_NODE";
}

void IRBinaryArithmeticExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
    stream->get()->write('\n');
    _irLeftNode->print(stream);
    stream->get()->write('\n');
    _irRightNode->print(stream);
}