//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-binary-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"


ASTBinaryExpressionNode::ASTBinaryExpressionNode(ASTExpressionNode* leftNode, ASTBinaryOperatorNode* binaryOperator, ASTExpressionNode* rightNode) {
    _leftNode = leftNode;
    _binaryOperator = binaryOperator;
    _rightNode = rightNode;
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