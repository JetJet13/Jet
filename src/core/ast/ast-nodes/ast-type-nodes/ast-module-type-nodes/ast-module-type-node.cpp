//
// Created by Johny Georges on 2026-05-30.
//

#include "ast-module-type-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTModuleTypeNode::ASTModuleTypeNode(std::shared_ptr<ASTModuleTypeSourceNode> source, std::shared_ptr<ASTModuleAccessTypeNode> moduleAccess, std::shared_ptr<ASTModuleTypeTargetNode> target) {
    _source = source;
    _moduleAccess = moduleAccess;
    _target = target;
    _children.push_back(_source);
    _children.push_back(_moduleAccess);
    _children.push_back(_target);
}

std::shared_ptr<ASTModuleTypeSourceNode> ASTModuleTypeNode::getSource() {
    return _source;
}

std::shared_ptr<ASTModuleTypeTargetNode> ASTModuleTypeNode::getTarget() {
    return _target;
}

std::string ASTModuleTypeNode::getModuleTargetName() {
    return _target->getId();
}

std::string ASTModuleTypeNode::getModuleName() {
    return _source->getId();
}

std::shared_ptr<Position> ASTModuleTypeNode::getStartPosition() {
    return _source->getStartPosition();
}

std::shared_ptr<Position> ASTModuleTypeNode::getEndPosition() {
    return _target->getEndPosition();
}

ASTNodeType ASTModuleTypeNode::getNodeType() {
    return AST_MODULE_TYPE_NODE;
}

std::string ASTModuleTypeNode::toString() {
    return "MODULE_TYPE";
}

bool ASTModuleTypeNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleTypeNode>(other);
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
