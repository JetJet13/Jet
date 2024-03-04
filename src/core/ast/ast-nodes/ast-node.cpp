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

bool ASTNode::isOneOf(std::vector<ASTNodeType> astNodeTypes) {
    return std::find(
            astNodeTypes.begin(),
            astNodeTypes.end(),
            this->getNodeType()) != astNodeTypes.end();
}

void ASTNode::print() {
    Logger::log(this->toString());
}

bool ASTNode::isSameAs(ASTNode* other) {
    return this->getNodeType() == other->getNodeType();
}

ASTNode* ASTNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode) {
    return this;
}