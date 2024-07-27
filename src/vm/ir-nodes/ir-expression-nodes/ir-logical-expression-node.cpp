//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-logical-expression-node.h"

IRLogicalExpressionNode::IRLogicalExpressionNode(ASTLogicalExpressionNode* astNode, llvm::BinaryOperator* irValue, IRType* type, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode, IRInstructionNode* sourceAllocation) {
    _astNode = astNode;
    _irValue = irValue;
    _type = type;
    _irLeftNode = irLeftNode;
    _irRightNode = irRightNode;
    _sourceAllocation = sourceAllocation;
}

llvm::Value * IRLogicalExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    auto leftNodeAllocation = builder->get()->CreateAlloca(_irLeftNode->getType());
    auto irLeftNodeValue = _irLeftNode->insertSelfIntoBlock(builder);
    builder->get()->CreateStore(irLeftNodeValue, leftNodeAllocation);
    auto leftNodeValue = builder->get()->CreateLoad(leftNodeAllocation->getAllocatedType(), leftNodeAllocation);

    auto rightNodeAllocation = builder->get()->CreateAlloca(_irRightNode->getType());
    auto irRightNodeValue = _irRightNode->insertSelfIntoBlock(builder);
    builder->get()->CreateStore(irRightNodeValue, rightNodeAllocation);
    auto rightNodeValue = builder->get()->CreateLoad(rightNodeAllocation->getAllocatedType(), rightNodeAllocation);

    return builder->get()->CreateBinOp(_irValue->getOpcode(), leftNodeValue, rightNodeValue);
}

IRType* IRLogicalExpressionNode::getIRType() {
    return _type;
}

llvm::BinaryOperator* IRLogicalExpressionNode::getValue() {
    return _irValue;
}

IRInstructionNode* IRLogicalExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
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