//
// Created by Johny Georges on 2024-03-27.
//

#include "ast-object-access-target-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTObjectAccessTargetNode::ASTObjectAccessTargetNode(std::shared_ptr<ASTIdentifierExpressionNode> target) {
    _target = target;
    _children.push_back(_target);
}

std::shared_ptr<ASTIdentifierExpressionNode> ASTObjectAccessTargetNode::getTarget() {
    return _target;
}

std::shared_ptr<Position> ASTObjectAccessTargetNode::getStartPosition() {
    return _target->getStartPosition();
}

std::shared_ptr<Position> ASTObjectAccessTargetNode::getEndPosition() {
    return _target->getEndPosition();
}

ASTNodeType ASTObjectAccessTargetNode::getNodeType() {
    return AST_OBJECT_ACCESS_TARGET_NODE;
}

std::string ASTObjectAccessTargetNode::toString() {
    return "OBJECT_ACCESS_TARGET";
}

bool ASTObjectAccessTargetNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTObjectAccessTargetNode>(other);
    return this->getTarget()->isSameAs(otherNode->getTarget());
}

void ASTObjectAccessTargetNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _target->print();
    Logger::log("----------");
}

std::string ASTObjectAccessTargetNode::toSourceCode() {
    return _target->toSourceCode();
}