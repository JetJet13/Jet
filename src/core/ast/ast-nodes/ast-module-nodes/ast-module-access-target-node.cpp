//
// Created by Johny Georges on 2024-11-05.
//

#include "ast-module-access-target-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleAccessTargetNode::ASTModuleAccessTargetNode(ASTIdentifierExpressionNode* target) {
    _target = target;
    _children.push_back(_target);
}

ASTIdentifierExpressionNode* ASTModuleAccessTargetNode::getTarget() {
    return _target;
}

Position* ASTModuleAccessTargetNode::getStartPosition() {
    return _target->getStartPosition();
}

Position* ASTModuleAccessTargetNode::getEndPosition() {
    return _target->getEndPosition();
}

ASTNodeType ASTModuleAccessTargetNode::getNodeType() {
    return AST_MODULE_ACCESS_TARGET_NODE;
}

std::string ASTModuleAccessTargetNode::toString() {
    return "MODULE_ACCESS_TARGET";
}

bool ASTModuleAccessTargetNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTModuleAccessTargetNode*)other;
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