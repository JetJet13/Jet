//
// Created by Johny Georges on 2024-03-27.
//

#include "ast-object-access-target-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTObjectAccessTargetNode::ASTObjectAccessTargetNode(ASTExpressionNode* target) {
    _target = target;
}

ASTExpressionNode* ASTObjectAccessTargetNode::getTarget() {
    return _target;
}

ASTNodeType ASTObjectAccessTargetNode::getNodeType() {
    return AST_OBJECT_ACCESS_TARGET_NODE;
}

std::string ASTObjectAccessTargetNode::toString() {
    return "OBJECT_ACCESS_TARGET";
}

bool ASTObjectAccessTargetNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTObjectAccessTargetNode*)other;
    return this->getTarget()->isSameAs(otherNode->getTarget());
}

void ASTObjectAccessTargetNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _target->print();
    Logger::log("----------");
}