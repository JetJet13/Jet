//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-expression-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTExpressionStatementNode::ASTExpressionStatementNode(ASTExpressionNode* expression) {
    _expression = expression;
    _children.push_back(_expression);
}

ASTExpressionNode* ASTExpressionStatementNode::getExpression() {
    return _expression;
}

ASTNodeType ASTExpressionStatementNode::getNodeType() {
    return AST_EXPRESSION_STATEMENT_NODE;
}

std::string ASTExpressionStatementNode::toString() {
    return "EXPRESSION_STATEMENT";
}

bool ASTExpressionStatementNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTExpressionStatementNode*)other;
    return this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTExpressionStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _expression->print();
    Logger::log("----------");
}