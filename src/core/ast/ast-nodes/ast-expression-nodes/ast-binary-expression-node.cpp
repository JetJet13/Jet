//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-binary-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTBinaryExpressionNode::ASTBinaryExpressionNode(ASTExpressionNode* leftNode, ASTBinaryOperatorNode* binaryOperator, ASTExpressionNode* rightNode) {
    _leftNode = leftNode;
    _binaryOperator = binaryOperator;
    _rightNode = rightNode;
    _children.push_back(_leftNode);
    _children.push_back(_binaryOperator);
    _children.push_back(_rightNode);
}

ASTExpressionNode* ASTBinaryExpressionNode::getLeftNode() {
    return _leftNode;
}

ASTExpressionNode* ASTBinaryExpressionNode::getRightNode() {
    return _rightNode;
}

ASTBinaryOperatorNode* ASTBinaryExpressionNode::getBinaryOperator() {
    return _binaryOperator;
}

void ASTBinaryExpressionNode::markAsGlobal() {
    _isGlobal = true;
    _leftNode->markAsGlobal();
    _rightNode->markAsGlobal();
}

Position* ASTBinaryExpressionNode::getStartPosition() {
    return _leftNode->getStartPosition();
}

Position* ASTBinaryExpressionNode::getEndPosition() {
    return _rightNode->getEndPosition();
}

ASTNodeType ASTBinaryExpressionNode::getNodeType() {
    return AST_BINARY_EXPRESSION_NODE;
}

std::string ASTBinaryExpressionNode::toString() {
    return "BINARY_EXPRESSION";
}

bool ASTBinaryExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTBinaryExpressionNode*)other;
    return this->getBinaryOperator()->isSameAs(otherNode->getBinaryOperator()) &&
           this->getLeftNode()->isSameAs(otherNode->getLeftNode()) &&
           this->getRightNode()->isSameAs(otherNode->getRightNode());
}

void ASTBinaryExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _leftNode->print();
    _binaryOperator->print();
    _rightNode->print();
    Logger::log("----------");
}

std::string ASTBinaryExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_leftNode)
    ->addWithWhitespace(_binaryOperator)
    ->addWithWhitespace(_rightNode);
    return sourceCodeBuilder.build();
}