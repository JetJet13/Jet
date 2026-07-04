//
// Created by Johny Georges on 2026-03-02.
//

#include "ast-binary-comparator-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTBinaryComparatorExpressionNode::ASTBinaryComparatorExpressionNode(std::shared_ptr<ASTExpressionNode> leftNode, std::shared_ptr<ASTBinaryComparatorOperatorNode> binaryOperator, std::shared_ptr<ASTExpressionNode> rightNode) {
    _leftNode = leftNode;
    _binaryOperator = binaryOperator;
    _rightNode = rightNode;
    _children.push_back(_leftNode);
    _children.push_back(_binaryOperator);
    _children.push_back(_rightNode);
}

std::shared_ptr<ASTExpressionNode> ASTBinaryComparatorExpressionNode::getLeftNode() {
    return _leftNode;
}

std::shared_ptr<ASTExpressionNode> ASTBinaryComparatorExpressionNode::getRightNode() {
    return _rightNode;
}

void ASTBinaryComparatorExpressionNode::setLeftTypeSignature(TypeSignature* typeSignature) {
    _leftTypeSignature = typeSignature;
}

void ASTBinaryComparatorExpressionNode::setRightTypeSignature(TypeSignature* typeSignature) {
    _rightTypeSignature = typeSignature;
}

TypeSignature* ASTBinaryComparatorExpressionNode::getLeftTypeSignature() {
    return _leftTypeSignature;
}

TypeSignature* ASTBinaryComparatorExpressionNode::getRightTypeSignature() {
    return _rightTypeSignature;
}

std::shared_ptr<ASTBinaryComparatorOperatorNode> ASTBinaryComparatorExpressionNode::getBinaryOperator() {
    return _binaryOperator;
}

Position* ASTBinaryComparatorExpressionNode::getStartPosition() {
    return _leftNode->getStartPosition();
}

Position* ASTBinaryComparatorExpressionNode::getEndPosition() {
    return _rightNode->getEndPosition();
}

ASTNodeType ASTBinaryComparatorExpressionNode::getNodeType() {
    return AST_BINARY_COMPARATOR_EXPRESSION_NODE;
}

std::string ASTBinaryComparatorExpressionNode::toString() {
    return "BINARY_COMPARATOR_EXPRESSION";
}

bool ASTBinaryComparatorExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTBinaryComparatorExpressionNode>(other);
    return this->getBinaryOperator()->isSameAs(otherNode->getBinaryOperator()) &&
           this->getLeftNode()->isSameAs(otherNode->getLeftNode()) &&
           this->getRightNode()->isSameAs(otherNode->getRightNode());
}

void ASTBinaryComparatorExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _leftNode->print();
    _binaryOperator->print();
    _rightNode->print();
    Logger::log("----------");
}

std::string ASTBinaryComparatorExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_leftNode)
            ->add(_binaryOperator)
            ->add(_rightNode);
    return sourceCodeBuilder.build();
}