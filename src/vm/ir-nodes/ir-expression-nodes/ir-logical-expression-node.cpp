//
// Created by Johny Georges on 2024-07-01.
//

#include "ir-logical-expression-node.h"

IRLogicalExpressionNode::IRLogicalExpressionNode(ASTLogicalExpressionNode* astNode, llvm::BinaryOperator* irValue, IRType* type, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode) {
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

bool IRLogicalExpressionNode::isReferenced() {
    return _node->isReferenced();
}


IRType* IRLogicalExpressionNode::getIRType() {
    return _type;
}

TypeSignature* IRLogicalExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
}

Position* IRLogicalExpressionNode::getStartPosition() {
    return _node->getStartPosition();
}

Position* IRLogicalExpressionNode::getEndPosition() {
    return _node->getEndPosition();
}

llvm::BinaryOperator* IRLogicalExpressionNode::getValue() {
    return _irValue;
}

IRExpressionNode* IRLogicalExpressionNode::getLeftNode() {
    return _irLeftNode;
}

IRExpressionNode* IRLogicalExpressionNode::getRightNode() {
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