//
// Created by Johny Georges on 2024-04-15.
//

#include "ast-import-module-list-by-wildcard-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTImportModuleListByWildcardItemNode::ASTImportModuleListByWildcardItemNode(ASTImportModuleNameNode* moduleName) {
    _moduleName = moduleName;
}

ASTImportModuleNameNode* ASTImportModuleListByWildcardItemNode::getModuleName() {
    return _moduleName;
}

ASTNodeType ASTImportModuleListByWildcardItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_NODE;
}

std::string ASTImportModuleListByWildcardItemNode::toString() {
    return "IMPORT_MODULE_LIST_BY_WILDCARD_ITEM";
}

bool ASTImportModuleListByWildcardItemNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTImportModuleListByWildcardItemNode*)other;
    return this->getModuleName()->isSameAs(otherNode->getModuleName());
}

void ASTImportModuleListByWildcardItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    Logger::log("----------");
}