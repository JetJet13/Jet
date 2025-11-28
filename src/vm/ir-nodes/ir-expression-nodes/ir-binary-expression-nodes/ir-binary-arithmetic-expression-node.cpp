//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-binary-arithmetic-expression-node.h"

IRBinaryArithmeticExpressionNode::IRBinaryArithmeticExpressionNode(ASTBinaryExpressionNode* astNode, llvm::BinaryOperator* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode, IRType* type) {
    _node = astNode;
    _irValue = irValue;
    _irLeftNode = irLeftNode;
    _irRightNode = irRightNode;
    _type = type;
}

void IRBinaryArithmeticExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irLeftNode->markAsGlobal();
    _irRightNode->markAsGlobal();
}

bool IRBinaryArithmeticExpressionNode::isReferenced() {
    return _node->isReferenced();
}

llvm::BinaryOperator* IRBinaryArithmeticExpressionNode::getValue() {
    return _irValue;
}

IRExpressionNode* IRBinaryArithmeticExpressionNode::getLeftNode() {
    return _irLeftNode;
}

IRExpressionNode* IRBinaryArithmeticExpressionNode::getRightNode() {
    return _irRightNode;
}

IRType* IRBinaryArithmeticExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRBinaryArithmeticExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
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