//
// Created by Johny Georges on 2024-06-29.
//

#include "ir-binary-comparison-expression-node.h"

IRBinaryComparisonExpressionNode::IRBinaryComparisonExpressionNode(ASTBinaryExpressionNode* astNode, llvm::CmpInst* irValue, IRExpressionNode* irLeftNode, IRExpressionNode* irRightNode, IRType* type) {
    _node = astNode;
    _irValue = irValue;
    _irLeftNode = irLeftNode;
    _irRightNode = irRightNode;
    _type = type;
}

void IRBinaryComparisonExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _irLeftNode->markAsGlobal();
    _irRightNode->markAsGlobal();
}

llvm::CmpInst* IRBinaryComparisonExpressionNode::getValue() {
    return _irValue;
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

TypeSignature* IRBinaryComparisonExpressionNode::getTypeSignature() {
    return _node->getTypeSignature();
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