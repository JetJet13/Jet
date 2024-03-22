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

bool ASTNode::isSameNodeTypeAs(ASTNode* other) {
    return this->getNodeType() == other->getNodeType();
}

void ASTNode::print() {
    Logger::log(this->toString());
}

int ASTNode::getPriority() {
    return _priority;
}

bool ASTNode::isHigherPriorityThan(ASTNode* other) {
    return this->getPriority() < other->getPriority();
}

bool ASTNode::isLowerPriorityThan(ASTNode* other) {
    return this->getPriority() > other->getPriority();
}

bool ASTNode::isSameAs(ASTNode* other) {
    return this->getNodeType() == other->getNodeType();
}

ASTNode* ASTNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {
    return this;
}