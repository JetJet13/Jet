//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-normal-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTModuleListNormalItemNode::ASTModuleListNormalItemNode(std::shared_ptr<ASTModuleNameNode> moduleName) {
    _moduleName = moduleName;
    _children.push_back(_moduleName);
}

std::shared_ptr<ASTModuleNameNode> ASTModuleListNormalItemNode::getModuleName() {
    return _moduleName;
}

Position* ASTModuleListNormalItemNode::getStartPosition() {
    return _moduleName->getStartPosition();
}

Position* ASTModuleListNormalItemNode::getEndPosition() {
    return _moduleName->getEndPosition();
}

ASTNodeType ASTModuleListNormalItemNode::getNodeType() {
    return AST_MODULE_LIST_NORMAL_ITEM_NODE;
}

std::string ASTModuleListNormalItemNode::toString() {
    return "MODULE_LIST_NORMAL_ITEM";
}

bool ASTModuleListNormalItemNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleListNormalItemNode>(other);
    return this->getModuleName()->isSameAs(otherNode->getModuleName());
}

void ASTModuleListNormalItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    Logger::log("----------");
}

std::string ASTModuleListNormalItemNode::toSourceCode() {
    return _moduleName->toSourceCode();
}