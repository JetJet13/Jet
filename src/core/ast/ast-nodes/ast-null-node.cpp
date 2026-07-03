//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-null-node.h"
#include "../../../shared/utils/logger/logger.h"

ASTNodeType ASTNullNode::getNodeType() {
    return AST_NULL_NODE;
}

std::string ASTNullNode::toString() {
    return "NULL";
}

Position* ASTNullNode::getStartPosition() {
    return new Position();
}

Position* ASTNullNode::getEndPosition() {
    return new Position();
}

bool ASTNullNode::isSameAs(ASTNode* other) {
    return !other->is(this->getNodeType());
}

void ASTNullNode::print() {
    Logger::log(this->toString());
}