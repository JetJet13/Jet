//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-alias-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTModuleListAliasItemNode::ASTModuleListAliasItemNode(ASTModuleNameNode* moduleName, ASTModuleAliasNameNode* aliasModuleName) {
    _moduleName = moduleName;
    _aliasModuleName = aliasModuleName;
    _children.push_back(_moduleName);
    _children.push_back(_aliasModuleName);
}

ASTModuleNameNode* ASTModuleListAliasItemNode::getModuleName() {
    return _moduleName;
}

ASTModuleAliasNameNode* ASTModuleListAliasItemNode::getAliasModuleName() {
    return _aliasModuleName;
}

ASTNodeType ASTModuleListAliasItemNode::getNodeType() {
    return AST_MODULE_LIST_ALIAS_ITEM_NODE;
}

std::string ASTModuleListAliasItemNode::toString() {
    return "MODULE_LIST_ALIAS_ITEM";
}

bool ASTModuleListAliasItemNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTModuleListAliasItemNode*)other;
    return this->getModuleName()->isSameAs(otherNode->getModuleName()) &&
            this->getAliasModuleName()->isSameAs(otherNode->getAliasModuleName()) ;
}

void ASTModuleListAliasItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    _aliasModuleName->print();
    Logger::log("----------");
}