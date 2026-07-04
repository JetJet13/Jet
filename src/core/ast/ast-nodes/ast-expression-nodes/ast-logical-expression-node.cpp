//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-logical-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTLogicalExpressionNode::ASTLogicalExpressionNode(std::shared_ptr<ASTExpressionNode> leftNode, std::shared_ptr<ASTLogicalOperatorNode> logicalOperator, std::shared_ptr<ASTExpressionNode> rightNode) {
    _leftNode = leftNode;
    _logicalOperator = logicalOperator;
    _rightNode = rightNode;
    _children.push_back(_leftNode);
    _children.push_back(_logicalOperator);
    _children.push_back(_rightNode);
}

std::shared_ptr<ASTExpressionNode> ASTLogicalExpressionNode::getLeftNode() {
    return _leftNode;
}

std::shared_ptr<ASTExpressionNode> ASTLogicalExpressionNode::getRightNode() {
    return _rightNode;
}

std::shared_ptr<ASTLogicalOperatorNode> ASTLogicalExpressionNode::getLogicalOperator() {
    return _logicalOperator;
}

Position* ASTLogicalExpressionNode::getStartPosition() {
    return _leftNode->getStartPosition();
}

Position* ASTLogicalExpressionNode::getEndPosition() {
    return _rightNode->getEndPosition();
}

ASTNodeType ASTLogicalExpressionNode::getNodeType() {
    return AST_LOGICAL_EXPRESSION_NODE;
}

std::string ASTLogicalExpressionNode::toString() {
    return "LOGICAL_EXPRESSION";
}

bool ASTLogicalExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTLogicalExpressionNode>(other);
    return this->getLogicalOperator()->isSameAs(otherNode->getLogicalOperator()) &&
           this->getLeftNode()->isSameAs(otherNode->getLeftNode()) &&
           this->getRightNode()->isSameAs(otherNode->getRightNode());
}

void ASTLogicalExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _leftNode->print();
    _logicalOperator->print();
    _rightNode->print();
    Logger::log("----------");
}

std::string ASTLogicalExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_leftNode)
    ->add(_logicalOperator)
    ->add(_rightNode);
    return sourceCodeBuilder.build();
}