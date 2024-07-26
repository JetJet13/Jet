//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-object-access-source-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTObjectAccessSourceNode::ASTObjectAccessSourceNode(ASTAggregateExpressionNode* source) {
    _source = source;
    _children.push_back(_source);
}

ASTAggregateExpressionNode* ASTObjectAccessSourceNode::getSource() {
    return _source;
}

AggregateTypeSignature<TypeSignature>* ASTObjectAccessSourceNode::getTypeSignature() {
    return (AggregateTypeSignature<TypeSignature>*)_source->getTypeSignature();
}

Position* ASTObjectAccessSourceNode::getStartPosition() {
    return _source->getStartPosition();
}

Position* ASTObjectAccessSourceNode::getEndPosition() {
    return _source->getEndPosition();
}

ASTNodeType ASTObjectAccessSourceNode::getNodeType() {
    return AST_OBJECT_ACCESS_SOURCE_NODE;
}

std::string ASTObjectAccessSourceNode::toString() {
    return "OBJECT_ACCESS_SOURCE";
}

bool ASTObjectAccessSourceNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTObjectAccessSourceNode*)other;
    return this->getSource()->isSameAs(otherNode->getSource());
}

void ASTObjectAccessSourceNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    Logger::log("----------");
}

std::string ASTObjectAccessSourceNode::toSourceCode() {
    return _source->toSourceCode();
}