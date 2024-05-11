//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-spread-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTModuleListSpreadItemNode::ASTModuleListSpreadItemNode(ASTModuleNameNode* moduleName) {
    _moduleName = moduleName;
    _children.push_back(_moduleName);
}

ASTModuleNameNode* ASTModuleListSpreadItemNode::getModuleName() {
    return _moduleName;
}

ASTNodeType ASTModuleListSpreadItemNode::getNodeType() {
    return AST_MODULE_LIST_SPREAD_ITEM_NODE;
}

std::string ASTModuleListSpreadItemNode::toString() {
    return "MODULE_LIST_SPREAD_ITEM";
}

bool ASTModuleListSpreadItemNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTModuleListSpreadItemNode*)other;
    return this->getModuleName()->isSameAs(otherNode->getModuleName());
}

void ASTModuleListSpreadItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _moduleName->print();
    Logger::log("----------");
}