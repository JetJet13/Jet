//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-for-source-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTForSourceNode::ASTForSourceNode(ASTExpressionNode* source) {
    _source = source;
    _children.push_back(_source);
}

ASTExpressionNode* ASTForSourceNode::getSource() {
    return _source;
}

void ASTForSourceNode::setTypeSignature(TypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignature* ASTForSourceNode::getTypeSignature() {
    return _typeSignature;
}

ASTNodeType ASTForSourceNode::getNodeType() {
    return AST_FOR_SOURCE_NODE;
}

std::string ASTForSourceNode::toString() {
    return "FOR_SOURCE";
}

bool ASTForSourceNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTForSourceNode*)other;
    return this->getSource()->isSameAs(otherNode->getSource());
}

void ASTForSourceNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    Logger::log("----------");
}