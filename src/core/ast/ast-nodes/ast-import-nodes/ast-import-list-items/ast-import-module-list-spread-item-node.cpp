//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-module-list-spread-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTImportModuleListSpreadItemNode::ASTImportModuleListSpreadItemNode(ASTImportModuleNameNode* moduleName) {
    _moduleName = moduleName;
}

ASTImportModuleNameNode* ASTImportModuleListSpreadItemNode::getModuleName() {
    return _moduleName;
}

ASTNodeType ASTImportModuleListSpreadItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_SPREAD_ITEM_NODE;
}

std::string ASTImportModuleListSpreadItemNode::toString() {
    return "IMPORT_MODULE_LIST_SPREAD_ITEM";
}

bool ASTImportModuleListSpreadItemNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTImportModuleListSpreadItemNode*)other;
    return this->getModuleName()->isSameAs(otherNode->getModuleName());
}

void ASTImportModuleListSpreadItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    Logger::log("----------");
}