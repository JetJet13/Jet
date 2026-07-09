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

std::shared_ptr<Position> ASTNullNode::getStartPosition() {
    return std::make_shared<Position>();
}

std::shared_ptr<Position> ASTNullNode::getEndPosition() {
    return std::make_shared<Position>();
}

bool ASTNullNode::isSameAs(std::shared_ptr<ASTNode> other) {
    return !other->is(this->getNodeType());
}

void ASTNullNode::print() {
    Logger::log(this->toString());
}