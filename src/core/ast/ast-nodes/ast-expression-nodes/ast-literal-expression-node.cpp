//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-literal-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTLiteralExpressionNode::ASTLiteralExpressionNode(std::shared_ptr<ASTLiteralNode> literalNode) {
    _literalNode = literalNode;
    _children.push_back(_literalNode);
}

std::shared_ptr<ASTLiteralNode> ASTLiteralExpressionNode::getLiteralNode() {
    return _literalNode;
}

std::shared_ptr<Position> ASTLiteralExpressionNode::getStartPosition() {
    return _literalNode->getStartPosition();
}

std::shared_ptr<Position> ASTLiteralExpressionNode::getEndPosition() {
    return _literalNode->getEndPosition();
}

ASTNodeType ASTLiteralExpressionNode::getNodeType() {
    return AST_LITERAL_EXPRESSION_NODE;
}

std::string ASTLiteralExpressionNode::toString() {
    return "LITERAL_EXPRESSION";
}

bool ASTLiteralExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTLiteralExpressionNode>(other);
    return this->getLiteralNode()->isSameAs(otherNode->getLiteralNode());
}

void ASTLiteralExpressionNode::print() {
    Logger::log(this->toString(), "-", _literalNode->toString());
}

std::string ASTLiteralExpressionNode::toSourceCode() {
    return _literalNode->toSourceCode();
}