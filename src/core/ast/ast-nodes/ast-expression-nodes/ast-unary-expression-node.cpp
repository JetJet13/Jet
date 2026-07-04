//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-unary-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTUnaryExpressionNode::ASTUnaryExpressionNode(std::shared_ptr<ASTUnaryOperatorNode> unaryOperator, std::shared_ptr<ASTExpressionNode> astExpressionNode) {
    _unaryOperator = unaryOperator;
    _expression = astExpressionNode;
    _children.push_back(_unaryOperator);
    _children.push_back(_expression);
}

std::shared_ptr<ASTExpressionNode> ASTUnaryExpressionNode::getExpressionNode() {
    return _expression;
}

std::shared_ptr<ASTUnaryOperatorNode> ASTUnaryExpressionNode::getUnaryOperatorNode() {
    return _unaryOperator;
}

Position* ASTUnaryExpressionNode::getStartPosition() {
    return _unaryOperator->getStartPosition();
}

Position* ASTUnaryExpressionNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTUnaryExpressionNode::getNodeType() {
    return AST_UNARY_EXPRESSION_NODE;
}

std::string ASTUnaryExpressionNode::toString() {
    return "UNARY_EXPRESSION";
}

bool ASTUnaryExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTUnaryExpressionNode>(other);
    return this->getUnaryOperatorNode()->isSameAs(otherNode->getUnaryOperatorNode()) &&
           this->getExpressionNode()->isSameAs(otherNode->getExpressionNode());
}

void ASTUnaryExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _unaryOperator->print();
    _expression->print();
    Logger::log("----------");
}

std::string ASTUnaryExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_unaryOperator)
    ->add(_expression);
    return sourceCodeBuilder.build();
}