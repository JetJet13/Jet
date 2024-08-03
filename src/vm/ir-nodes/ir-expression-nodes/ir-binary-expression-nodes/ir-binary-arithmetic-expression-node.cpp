//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-binary-arithmetic-expression-node.h"

IRBinaryArithmeticExpressionNode::IRBinaryArithmeticExpressionNode(ASTBinaryExpressionNode* astNode, llvm::BinaryOperator* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode, IRPointerType* type, IRInstructionNode* sourceAllocation) {
    _astNode = astNode;
    _irValue = irValue;
    _irLeftNode = irLeftNode;
    _irRightNode = irRightNode;
    _type = type;
    _sourceAllocation = sourceAllocation;
}

llvm::Value* IRBinaryArithmeticExpressionNode::insertSelfIntoBlock(std::unique_ptr<llvm::IRBuilder<>>*  builder) {
    auto allocation = builder->get()->Insert(_sourceAllocation->getValue());

    auto irLeftNodeValue = _irLeftNode->insertSelfIntoBlock(builder);
    auto leftNodeValue = builder->get()->CreateLoad(_irLeftNode->getIRType()->getPointerSourceIRType()->getType(), irLeftNodeValue);

    auto irRightNodeValue = _irRightNode->insertSelfIntoBlock(builder);
    auto rightNodeValue = builder->get()->CreateLoad(_irRightNode->getIRType()->getPointerSourceIRType()->getType(), irRightNodeValue);

    auto result = builder->get()->CreateBinOp(_irValue->getOpcode(), leftNodeValue, rightNodeValue);
    builder->get()->CreateStore(result, allocation);
    return allocation;
}

llvm::BinaryOperator* IRBinaryArithmeticExpressionNode::getValue() {
    return _irValue;
}

IRInstructionNode* IRBinaryArithmeticExpressionNode::getSourceAllocation() {
    return _sourceAllocation;
}

IRPointerType* IRBinaryArithmeticExpressionNode::getIRType() {
    return _type;
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