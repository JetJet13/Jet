//
// Created by Johny Georges on 2024-02-08.
//

#include "ast-logical-operator-node.h"

ASTLogicalOperatorNode::ASTLogicalOperatorNode(Lexeme* logicalOperator) {
    _logicalOperator = logicalOperator;
}

Lexeme* ASTLogicalOperatorNode::getOperator() {
    return _logicalOperator;
}

ASTNodeType ASTLogicalOperatorNode::getNodeType() {
    return AST_LOGICAL_OPERATOR_NODE;
}

std::string ASTLogicalOperatorNode::toString() {
    return "LOGICAL_OPERATOR";
}

bool ASTLogicalOperatorNode::isEqual(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTLogicalOperatorNode*)other;
    return this->getOperator()->isEqual(otherNode->getOperator());
}