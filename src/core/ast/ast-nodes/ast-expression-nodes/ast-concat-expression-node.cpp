//
// Created by Johny Georges on 2025-06-07.
//

#include "ast-concat-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTConcatExpressionNode::ASTConcatExpressionNode(ASTExpressionNode* leftNode, ASTConcatNode* concatNode, ASTExpressionNode* rightNode) {
    _leftNode = leftNode;
    _concatNode = concatNode;
    _rightNode = rightNode;
    _children.push_back(_leftNode);
    _children.push_back(_concatNode);
    _children.push_back(_rightNode);
}

ASTExpressionNode* ASTConcatExpressionNode::getLeftNode() {
    return _leftNode;
}

ASTExpressionNode* ASTConcatExpressionNode::getRightNode() {
    return _rightNode;
}

ASTConcatNode* ASTConcatExpressionNode::getConcatNode() {
    return _concatNode;
}

void ASTConcatExpressionNode::markAsReferenced() {
    _isReferenced = true;
    _leftNode->markAsReferenced();
    _rightNode->markAsReferenced();
}

Position* ASTConcatExpressionNode::getStartPosition() {
    return _leftNode->getStartPosition();
}

Position* ASTConcatExpressionNode::getEndPosition() {
    return _rightNode->getEndPosition();
}

ASTNodeType ASTConcatExpressionNode::getNodeType() {
    return AST_CONCAT_EXPRESSION_NODE;
}

std::string ASTConcatExpressionNode::toString() {
    return "CONCAT_EXPRESSION";
}

bool ASTConcatExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTConcatExpressionNode*)other;
    return this->getLeftNode()->isSameAs(otherNode->getLeftNode()) &&
           this->getRightNode()->isSameAs(otherNode->getRightNode());
}

void ASTConcatExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _leftNode->print();
    _concatNode->print();
    _rightNode->print();
    Logger::log("----------");
}

std::string ASTConcatExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_leftNode)
            ->add(_concatNode)
            ->add(_rightNode);
    return sourceCodeBuilder.build();
}