//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-expression-statement-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTExpressionStatementNode::ASTExpressionStatementNode(std::shared_ptr<ASTExpressionNode> expression) {
    _expression = expression;
    _children.push_back(_expression);
}

std::shared_ptr<ASTExpressionNode> ASTExpressionStatementNode::getExpression() {
    return _expression;
}

std::shared_ptr<Position> ASTExpressionStatementNode::getStartPosition() {
    return _expression->getStartPosition();
}

std::shared_ptr<Position> ASTExpressionStatementNode::getEndPosition() {
    return _expression->getEndPosition();
}

ASTNodeType ASTExpressionStatementNode::getNodeType() {
    return AST_EXPRESSION_STATEMENT_NODE;
}

std::string ASTExpressionStatementNode::toString() {
    return "EXPRESSION_STATEMENT";
}

bool ASTExpressionStatementNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTExpressionStatementNode>(other);
    return this->getExpression()->isSameAs(otherNode->getExpression());
}

void ASTExpressionStatementNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _expression->print();
    Logger::log("----------");
}

std::string ASTExpressionStatementNode::toSourceCode() {
    return _expression->toSourceCode();
}