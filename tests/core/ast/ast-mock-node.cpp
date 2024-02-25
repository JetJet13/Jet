//
// Created by Johny Georges on 2024-02-24.
//

#include "ast-mock-node.h"

ASTMockNode::ASTMockNode(ASTNodeType astNodeType) {
    _nodeType = astNodeType;
}

ASTNodeType ASTMockNode::getNodeType() {
    return _nodeType;
}

std::string ASTMockNode::toString() {
    return "MOCK [" + std::to_string(_nodeType) + "]";
}