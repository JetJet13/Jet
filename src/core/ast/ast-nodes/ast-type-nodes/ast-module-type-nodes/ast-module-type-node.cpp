//
// Created by Johny Georges on 2026-05-30.
//

#include "ast-module-type-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTModuleTypeNode::ASTModuleTypeNode(ASTModuleTypeSourceNode* source, ASTModuleAccessTypeNode* moduleAccess, ASTModuleTypeTargetNode* target) {
    _source = source;
    _moduleAccess = moduleAccess;
    _target = target;
    _children.push_back(_source);
    _children.push_back(_moduleAccess);
    _children.push_back(_target);
}

ASTModuleTypeSourceNode* ASTModuleTypeNode::getSource() {
    return _source;
}

ASTModuleTypeTargetNode* ASTModuleTypeNode::getTarget() {
    return _target;
}

std::string ASTModuleTypeNode::getModuleTargetName() {
    return _target->getId();
}

std::string ASTModuleTypeNode::getModuleName() {
    return _source->getId();
}

Position* ASTModuleTypeNode::getStartPosition() {
    return _source->getStartPosition();
}

Position* ASTModuleTypeNode::getEndPosition() {
    return _target->getEndPosition();
}

ASTNodeType ASTModuleTypeNode::getNodeType() {
    return AST_MODULE_TYPE_NODE;
}

std::string ASTModuleTypeNode::toString() {
    return "MODULE_TYPE";
}

bool ASTModuleTypeNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTModuleTypeNode*)other;
    return this->getSource()->isSameAs(otherNode->getSource()) &&
           this->getTarget()->isSameAs(otherNode->getTarget());
}

void ASTModuleTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _source->print();
    _target->print();
    Logger::log("----------");
}

std::string ASTModuleTypeNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_source)
    ->add(_moduleAccess)
    ->add(_target);
    return sourceCodeBuilder.build();
}
