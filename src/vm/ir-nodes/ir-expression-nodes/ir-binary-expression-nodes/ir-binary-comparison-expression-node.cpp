//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-binary-comparison-expression-node.h"

IRBinaryComparisonExpressionNode::IRBinaryComparisonExpressionNode(ASTBinaryExpressionNode* astNode, llvm::CmpInst* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode) {
    _astNode = astNode;
    _irValue = irValue;
    _irLeftNode = irLeftNode;
    _irRightNode = irRightNode;
}

llvm::Value * IRBinaryComparisonExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder, llvm::Value *parent) {
    auto leftNodeAllocation = builder->get()->CreateAlloca(_irLeftNode->getIRType());
    _irLeftNode->insertSelfIntoBlock(builder, leftNodeAllocation);
    auto leftNodeValue = builder->get()->CreateLoad(leftNodeAllocation->getAllocatedType(), leftNodeAllocation);

    auto rightNodeAllocation = builder->get()->CreateAlloca(_irRightNode->getIRType());
    _irRightNode->insertSelfIntoBlock(builder, rightNodeAllocation);
    auto rightNodeValue = builder->get()->CreateLoad(rightNodeAllocation->getAllocatedType(), rightNodeAllocation);

    auto binaryResult = builder->get()->CreateCmp(_irValue->getPredicate(), leftNodeValue, rightNodeValue);

    return builder->get()->CreateStore(binaryResult, parent);
}

llvm::CmpInst* IRBinaryComparisonExpressionNode::getIRValue() {
    return _irValue;
}

IRNodeType IRBinaryComparisonExpressionNode::getNodeType() {
    return IR_BINARY_COMPARISON_EXPRESSION_NODE;
}

std::string IRBinaryComparisonExpressionNode::toString() {
    return "IR_BINARY_COMPARISON_EXPRESSION_NODE";
}

void IRBinaryComparisonExpressionNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irValue->print(**stream);
    stream->get()->write('\n');
    _irLeftNode->print(stream);
    stream->get()->write('\n');
    _irRightNode->print(stream);
}