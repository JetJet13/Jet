//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-binary-comparison-expression-node.h"

IRBinaryComparisonExpressionNode::IRBinaryComparisonExpressionNode(ASTBinaryExpressionNode* astNode, llvm::CmpInst* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode, IRType* type, IRInstructionNode* sourceAllocation) {
    _astNode = astNode;
    _irValue = irValue;
    _irLeftNode = irLeftNode;
    _irRightNode = irRightNode;
    _type = type;
    _sourceAllocation = sourceAllocation;
}

llvm::Value * IRBinaryComparisonExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    auto leftNodeAllocation = builder->get()->CreateAlloca(_irLeftNode->getType());
    auto irLeftNodeValue = _irLeftNode->insertSelfIntoBlock(builder);
    builder->get()->CreateStore(irLeftNodeValue, leftNodeAllocation);
    auto leftNodeValue = builder->get()->CreateLoad(leftNodeAllocation->getAllocatedType(), leftNodeAllocation);

    auto rightNodeAllocation = builder->get()->CreateAlloca(_irRightNode->getType());
    auto irRightNodeValue = _irRightNode->insertSelfIntoBlock(builder);
    builder->get()->CreateStore(irRightNodeValue, rightNodeAllocation);
    auto rightNodeValue = builder->get()->CreateLoad(rightNodeAllocation->getAllocatedType(), rightNodeAllocation);

    return builder->get()->CreateCmp(_irValue->getPredicate(), leftNodeValue, rightNodeValue);
}

llvm::CmpInst* IRBinaryComparisonExpressionNode::getValue() {
    return _irValue;
}

IRInstructionNode* IRBinaryComparisonExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
}

IRType* IRBinaryComparisonExpressionNode::getIRType() {
    return _type;
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