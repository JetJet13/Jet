//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-item-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportModuleListItemNode::ASTImportModuleListItemNode(ASTModuleListBaseItemNode* item) {
    _item = item;
}

ASTModuleListBaseItemNode* ASTImportModuleListItemNode::getItem() {
    return _item;
}

ASTNodeType ASTImportModuleListItemNode::getNodeType() {
    return AST_MODULE_LIST_ITEM_NODE;
}

std::string ASTImportModuleListItemNode::toString() {
    return "MODULE_LIST_ITEM";
}

bool ASTImportModuleListItemNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTImportModuleListItemNode*)other;
    return _item->isSameAs(otherNode->getItem());
}

void ASTImportModuleListItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _item->print();
    Logger::log("----------");
}