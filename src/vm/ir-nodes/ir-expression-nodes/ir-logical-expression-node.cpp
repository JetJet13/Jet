//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-logical-expression-node.h"

IRLogicalExpressionNode::IRLogicalExpressionNode(std::shared_ptr<ASTLogicalExpressionNode> astNode, llvm::BinaryOperator* irValue, std::shared_ptr<IRType> type, std::shared_ptr<IRExpressionNode> irLeftNode, std::shared_ptr<IRExpressionNode> irRightNode) {
    _node = astNode;
    _irValue = irValue;
    _type = type;
    _irLeftNode = irLeftNode;
    _irRightNode = irRightNode;
}

void IRLogicalExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irLeftNode->markAsGlobal();
    _irRightNode->markAsGlobal();
}

std::shared_ptr<IRType> IRLogicalExpressionNode::getIRType() {
    return _type;
}

std::shared_ptr<TypeSignature> IRLogicalExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

std::shared_ptr<Position> IRLogicalExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

std::shared_ptr<Position> IRLogicalExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

llvm::BinaryOperator* IRLogicalExpressionNode::getValue() {
    return _irValue;
}

std::shared_ptr<IRExpressionNode> IRLogicalExpressionNode::getLeftNode() {
    return _irLeftNode;
}

std::shared_ptr<IRExpressionNode> IRLogicalExpressionNode::getRightNode() {
    return _irRightNode;
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