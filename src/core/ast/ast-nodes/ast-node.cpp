//
// Created by Johny Georges on 2024-01-12.
//

#include "ast-node.h"


void ASTNode::setParentNode(ASTNode* parentNode) {
    _parentNode = parentNode;
}

bool ASTNode::is(ASTNodeType astNodeType) {
    return this->getNodeType() == astNodeType;
}

