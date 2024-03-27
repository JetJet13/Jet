//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-object-access-source-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTObjectAccessSourceNode::ASTObjectAccessSourceNode(ASTExpressionNode* source) {
    _source = source;
}

ASTExpressionNode* ASTObjectAccessSourceNode::getSource() {
    return _source;
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