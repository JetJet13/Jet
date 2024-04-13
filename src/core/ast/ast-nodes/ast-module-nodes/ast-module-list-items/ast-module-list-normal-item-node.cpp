//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-normal-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTImportModuleListNormalItemNode::ASTImportModuleListNormalItemNode(ASTPackageNameNode* moduleName) {
    _moduleName = moduleName;
}

ASTPackageNameNode* ASTImportModuleListNormalItemNode::getModuleName() {
    return _moduleName;
}

ASTNodeType ASTImportModuleListNormalItemNode::getNodeType() {
    return AST_MODULE_LIST_NORMAL_ITEM_NODE;
}

std::string ASTImportModuleListNormalItemNode::toString() {
    return "MODULE_LIST_NORMAL_ITEM";
}

bool ASTImportModuleListNormalItemNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTImportModuleListNormalItemNode*)other;
    return this->getModuleName()->isSameAs(otherNode->getModuleName());
}

void ASTImportModuleListNormalItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    Logger::log("----------");
}