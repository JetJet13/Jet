//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-module-list-alias-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTImportModuleListAliasItemNode::ASTImportModuleListAliasItemNode(ASTImportModuleNameNode* moduleName, ASTPackageAliasNameNode* aliasModuleName) {
    _moduleName = moduleName;
    _aliasModuleName = aliasModuleName;
}

ASTImportModuleNameNode* ASTImportModuleListAliasItemNode::getModuleName() {
    return _moduleName;
}

ASTPackageAliasNameNode* ASTImportModuleListAliasItemNode::getAliasModuleName() {
    return _aliasModuleName;
}

ASTNodeType ASTImportModuleListAliasItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_ALIAS_ITEM_NODE;
}

std::string ASTImportModuleListAliasItemNode::toString() {
    return "IMPORT_MODULE_LIST_ALIAS_ITEM";
}

bool ASTImportModuleListAliasItemNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTImportModuleListAliasItemNode*)other;
    return this->getModuleName()->isSameAs(otherNode->getModuleName()) &&
            this->getAliasModuleName()->isSameAs(otherNode->getAliasModuleName()) ;
}

void ASTImportModuleListAliasItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    _aliasModuleName->print();
    Logger::log("----------");
}