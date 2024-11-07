//
// Created by Johny Georges on 2024-11-05.
//

#include "ast-module-access-source-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleAccessSourceNode::ASTModuleAccessSourceNode(ASTIdentifierExpressionNode* source) {
    _source = source;
    _children.push_back(_source);
}

ASTIdentifierExpressionNode* ASTModuleAccessSourceNode::getSource() {
    return _source;
}

Position* ASTModuleAccessSourceNode::getStartPosition() {
    return _source->getStartPosition();
}

Position* ASTModuleAccessSourceNode::getEndPosition() {
    return _source->getEndPosition();
}

ASTNodeType ASTModuleAccessSourceNode::getNodeType() {
    return AST_MODULE_ACCESS_SOURCE_NODE;
}

std::string ASTModuleAccessSourceNode::toString() {
    return "MODULE_ACCESS_SOURCE";
}

bool ASTModuleAccessSourceNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTModuleAccessSourceNode*)other;
    return this->getSource()->isSameAs(otherNode->getSource());
}

void ASTModuleAccessSourceNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    Logger::log("----------");
}

std::string ASTModuleAccessSourceNode::toSourceCode() {
    return _source->toSourceCode();
}