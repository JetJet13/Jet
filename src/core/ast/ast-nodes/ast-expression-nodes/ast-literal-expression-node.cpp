//
// Created by Johny Georges on 2024-02-17.
//

#include "ast-literal-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTLiteralExpressionNode::ASTLiteralExpressionNode(ASTLiteralNode* literalNode) {
    _literalNode = literalNode;
}

ASTLiteralNode* ASTLiteralExpressionNode::getLiteralNode() {
    return _literalNode;
}

ASTNodeType ASTLiteralExpressionNode::getNodeType() {
    return AST_LITERAL_EXPRESSION_NODE;
}

std::string ASTLiteralExpressionNode::toString() {
    return "LITERAL_EXPRESSION";
}

bool ASTLiteralExpressionNode::isEqual(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    Logger::log("ASTLiteralExpressionNode", "other node is same type");
    auto otherNode = (ASTLiteralExpressionNode*)other;
    return this->getLiteralNode()->isEqual(otherNode->getLiteralNode());
}