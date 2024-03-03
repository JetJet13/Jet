//
// Created by Johny Georges on 2024-01-12.
//

#include "ast-node.h"
#include "../../../shared/utils/logger/logger.h"


void ASTNode::setParentNode(ASTNode* parentNode) {
    _parentNode = parentNode;
}

bool ASTNode::is(ASTNodeType astNodeType) {
    return this->getNodeType() == astNodeType;
}

void ASTNode::print() {
    Logger::log(this->toString());
}

