//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-for-in-source-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTForInSourceNode::ASTForInSourceNode(ASTExpressionNode* source) {
    _source = source;
    _children.push_back(_source);
}

ASTExpressionNode* ASTForInSourceNode::getSource() {
    return _source;
}

void ASTForInSourceNode::setTypeSignature(TypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignature* ASTForInSourceNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTForInSourceNode::getStartPosition() {
    return _source->getStartPosition();
}

Position* ASTForInSourceNode::getEndPosition() {
    return _source->getEndPosition();
}

ASTNodeType ASTForInSourceNode::getNodeType() {
    return AST_FOR_IN_SOURCE_NODE;
}

std::string ASTForInSourceNode::toString() {
    return "FOR_IN_SOURCE";
}

bool ASTForInSourceNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTForInSourceNode*)other;
    return this->getSource()->isSameAs(otherNode->getSource());
}

void ASTForInSourceNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    Logger::log("----------");
}

std::string ASTForInSourceNode::toSourceCode() {
    return _source->toSourceCode();
}