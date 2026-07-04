//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-binary-comparison-expression-node.h"

IRBinaryComparisonExpressionNode::IRBinaryComparisonExpressionNode(std::shared_ptr<ASTBinaryComparatorExpressionNode> astNode, llvm::CmpInst* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode, IRType* type, IRType* leftIrType, IRType* rightIrType) {
    _node = astNode;
    _irValue = irValue;
    _irLeftNode = irLeftNode;
    _irRightNode = irRightNode;
    _type = type;
    _leftIrType = leftIrType;
    _rightIrType = rightIrType;
}

void IRBinaryComparisonExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irLeftNode->markAsGlobal();
    _irRightNode->markAsGlobal();
}

llvm::CmpInst* IRBinaryComparisonExpressionNode::getValue() {
    return _irValue;
}

bool IRBinaryComparisonExpressionNode::isPredicateEqual() {
    return _irValue->getPredicate() == llvm::CmpInst::Predicate::ICMP_EQ;
}

bool IRBinaryComparisonExpressionNode::isPredicateNotEqual() {
    return _irValue->getPredicate() == llvm::CmpInst::Predicate::ICMP_NE;
}

IRType* IRBinaryComparisonExpressionNode::getLeftIrType() {
    return _leftIrType;
}

IRType* IRBinaryComparisonExpressionNode::getRightIrType() {
    return _rightIrType;
}

IRExpressionNode* IRBinaryComparisonExpressionNode::getLeftNode() {
    return _irLeftNode;
}

IRExpressionNode* IRBinaryComparisonExpressionNode::getRightNode() {
    return _irRightNode;
}

IRType* IRBinaryComparisonExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRBinaryComparisonExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRBinaryComparisonExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRBinaryComparisonExpressionNode::getEndPosition() {
    return _node->getEndPosition();
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