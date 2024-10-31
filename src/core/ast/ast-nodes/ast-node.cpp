//
// Created by Johny Georges on 2024-01-12.
//

#include "ast-node.h"

#include <utility>
#include "../../../shared/utils/logger/logger.h"
#include "../../type-signature/unknown-type-signature/unknown-type-signature.h"

std::string ASTNode::getId() {
    return _id;
}

ASTNode* ASTNode::setId(std::string id) {
    _id = id;
    return this;
}

std::optional<ASTNode*> ASTNode::getParentNode() {
    return _parentNode;
}

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

std::string ASTNode::toSourceCode() {
    throw std::logic_error("toSourceCode not implemented: " + this->toString());
}

TypeSignature* ASTNode::getTypeSignature() {
    throw std::logic_error("get type-signature not implemented: " + this->toString());
}

std::vector<ASTNode*> ASTNode::getChildren() {
    return _children;
}

bool ASTNode::isExportable() {
    return false;
}

unsigned int ASTNode::getPriority() {
    return _priority;
}

bool ASTNode::isHigherPriorityThan(ASTNode* other) {
    return this->getPriority() < other->getPriority();
}

bool ASTNode::isLowerPriorityThan(ASTNode* other) {
    return this->getPriority() > other->getPriority();
}

Position* ASTNode::getStartPosition() {
    throw std::logic_error("get start-position not implemented: " + this->toString());
}

Position* ASTNode::getEndPosition() {
    throw std::logic_error("get end-position not implemented: " + this->toString());
}

bool ASTNode::isSameAs(ASTNode* other) {
    return this->getNodeType() == other->getNodeType();
}

ASTNode* ASTNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {
    return this;
}