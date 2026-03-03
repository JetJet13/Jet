//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-binary-arithmetic-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTBinaryArithmeticExpressionNode::ASTBinaryArithmeticExpressionNode(ASTExpressionNode* leftNode, ASTBinaryArithmeticOperatorNode* binaryOperator, ASTExpressionNode* rightNode) {
    _leftNode = leftNode;
    _binaryOperator = binaryOperator;
    _rightNode = rightNode;
    _children.push_back(_leftNode);
    _children.push_back(_binaryOperator);
    _children.push_back(_rightNode);
}

ASTExpressionNode* ASTBinaryArithmeticExpressionNode::getLeftNode() {
    return _leftNode;
}

ASTExpressionNode* ASTBinaryArithmeticExpressionNode::getRightNode() {
    return _rightNode;
}

void ASTBinaryArithmeticExpressionNode::setLeftTypeSignature(TypeSignature* typeSignature) {
    _leftTypeSignature = typeSignature;
}

void ASTBinaryArithmeticExpressionNode::setRightTypeSignature(TypeSignature* typeSignature) {
    _rightTypeSignature = typeSignature;
}

TypeSignature* ASTBinaryArithmeticExpressionNode::getLeftTypeSignature() {
    return _leftTypeSignature;
}

TypeSignature* ASTBinaryArithmeticExpressionNode::getRightTypeSignature() {
    return _rightTypeSignature;
}

ASTBinaryArithmeticOperatorNode* ASTBinaryArithmeticExpressionNode::getBinaryOperator() {
    return _binaryOperator;
}

Position* ASTBinaryArithmeticExpressionNode::getStartPosition() {
    return _leftNode->getStartPosition();
}

Position* ASTBinaryArithmeticExpressionNode::getEndPosition() {
    return _rightNode->getEndPosition();
}

ASTNodeType ASTBinaryArithmeticExpressionNode::getNodeType() {
    return AST_BINARY_ARITHMETIC_EXPRESSION_NODE;
}

std::string ASTBinaryArithmeticExpressionNode::toString() {
    return "BINARY_ARITHMETIC_EXPRESSION";
}

bool ASTBinaryArithmeticExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTBinaryArithmeticExpressionNode*)other;
    return this->getBinaryOperator()->isSameAs(otherNode->getBinaryOperator()) &&
           this->getLeftNode()->isSameAs(otherNode->getLeftNode()) &&
           this->getRightNode()->isSameAs(otherNode->getRightNode());
}

void ASTBinaryArithmeticExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _leftNode->print();
    _binaryOperator->print();
    _rightNode->print();
    Logger::log("----------");
}

std::string ASTBinaryArithmeticExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_leftNode)
    ->add(_binaryOperator)
    ->add(_rightNode);
    return sourceCodeBuilder.build();
}