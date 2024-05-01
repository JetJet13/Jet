//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-unary-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-type-nodes/types/literal-type-factory.h"


ASTUnaryExpressionNode::ASTUnaryExpressionNode(ASTUnaryOperatorNode* unaryOperator, ASTExpressionNode* astExpressionNode) {
    _unaryOperator = unaryOperator;
    _expression = astExpressionNode;
}

ASTExpressionNode* ASTUnaryExpressionNode::getExpressionNode() {
    return _expression;
}

ASTUnaryOperatorNode* ASTUnaryExpressionNode::getUnaryOperatorNode() {
    return _unaryOperator;
}

ASTNodeType ASTUnaryExpressionNode::getNodeType() {
    return AST_UNARY_EXPRESSION_NODE;
}

std::string ASTUnaryExpressionNode::toString() {
    return "UNARY_EXPRESSION";
}

bool ASTUnaryExpressionNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTUnaryExpressionNode*)other;
    return this->getUnaryOperatorNode()->isSameAs(otherNode->getUnaryOperatorNode()) &&
           this->getExpressionNode()->isSameAs(otherNode->getExpressionNode());
}

void ASTUnaryExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _unaryOperator->print();
    _expression->print();
    Logger::log("----------");
}

TypeSignature* ASTUnaryExpressionNode::getType() {
    if (_unaryOperator->getOperator()->getToken()->getSymbol()->isBang()) {
        return LiteralTypeFactory::createBooleanLiteralType();
    }
    return _expression->getType();
}