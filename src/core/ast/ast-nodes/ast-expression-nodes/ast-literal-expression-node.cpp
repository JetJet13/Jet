//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-literal-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTLiteralExpressionNode::ASTLiteralExpressionNode(ASTLiteralNode* literalNode) {
    _literalNode = literalNode;
    _children.push_back(_literalNode);
}

ASTLiteralNode* ASTLiteralExpressionNode::getLiteralNode() {
    return _literalNode;
}

Position* ASTLiteralExpressionNode::getStartPosition() {
    return _literalNode->getStartPosition();
}

Position* ASTLiteralExpressionNode::getEndPosition() {
    return _literalNode->getEndPosition();
}

ASTNodeType ASTLiteralExpressionNode::getNodeType() {
    return AST_LITERAL_EXPRESSION_NODE;
}

std::string ASTLiteralExpressionNode::toString() {
    return "LITERAL_EXPRESSION";
}

bool ASTLiteralExpressionNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTLiteralExpressionNode*)other;
    return this->getLiteralNode()->isSameAs(otherNode->getLiteralNode());
}

void ASTLiteralExpressionNode::print() {
    Logger::log(this->toString(), "-", _literalNode->toString());
}

std::string ASTLiteralExpressionNode::toSourceCode() {
    return _literalNode->toSourceCode();
}