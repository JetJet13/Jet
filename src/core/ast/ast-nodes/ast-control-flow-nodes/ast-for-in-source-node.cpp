//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-for-in-source-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTForInSourceNode::ASTForInSourceNode(std::shared_ptr<ASTExpressionNode> source) {
    _source = source;
    _children.push_back(_source);
}

std::shared_ptr<ASTExpressionNode> ASTForInSourceNode::getSource() {
    return _source;
}

void ASTForInSourceNode::setTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<TypeSignature> ASTForInSourceNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTForInSourceNode::getStartPosition() {
    return _source->getStartPosition();
}

std::shared_ptr<Position> ASTForInSourceNode::getEndPosition() {
    return _source->getEndPosition();
}

ASTNodeType ASTForInSourceNode::getNodeType() {
    return AST_FOR_IN_SOURCE_NODE;
}

std::string ASTForInSourceNode::toString() {
    return "FOR_IN_SOURCE";
}

bool ASTForInSourceNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTForInSourceNode>(other);
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