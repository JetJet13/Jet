//
// Created by Johny Georges on 2024-11-05.
//

#include "ast-module-access-target-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleAccessTargetNode::ASTModuleAccessTargetNode(std::shared_ptr<ASTIdentifierExpressionNode> target) {
    _target = target;
    _children.push_back(_target);
}

std::shared_ptr<ASTIdentifierExpressionNode> ASTModuleAccessTargetNode::getTarget() {
    return _target;
}

std::shared_ptr<Position> ASTModuleAccessTargetNode::getStartPosition() {
    return _target->getStartPosition();
}

std::shared_ptr<Position> ASTModuleAccessTargetNode::getEndPosition() {
    return _target->getEndPosition();
}

ASTNodeType ASTModuleAccessTargetNode::getNodeType() {
    return AST_MODULE_ACCESS_TARGET_NODE;
}

std::string ASTModuleAccessTargetNode::toString() {
    return "MODULE_ACCESS_TARGET";
}

bool ASTModuleAccessTargetNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleAccessTargetNode>(other);
    return this->getTarget()->isSameAs(otherNode->getTarget());
}

void ASTModuleAccessTargetNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _target->print();
    Logger::log("----------");
}

std::string ASTModuleAccessTargetNode::toSourceCode() {
    return _target->toSourceCode();
}