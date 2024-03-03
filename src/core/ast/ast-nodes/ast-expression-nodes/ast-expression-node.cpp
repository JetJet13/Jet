//
// Created by Johny Georges on 2024-01-12.
//

#include "ast-expression-node.h"

ASTExpressionNode::ASTExpressionNode() {
    _childNodes = {};
}

void ASTExpressionNode::addChildNode(ASTNode* astNode) {
    _childNodes.push_back(astNode);
}

ASTNodeType ASTExpressionNode::getNodeType() {
    return AST_EXPRESSION_NODE;
}

std::string ASTExpressionNode::toString() {
    return "EXPRESSION";
}

bool ASTExpressionNode::isSameAs(ASTNode *other) {
    return other->is(this->getNodeType());
}