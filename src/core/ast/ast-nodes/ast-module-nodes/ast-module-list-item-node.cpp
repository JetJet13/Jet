//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-item-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleListItemNode::ASTModuleListItemNode(ASTModuleListBaseItemNode* item) {
    _item = item;
    _children.push_back(_item);
}

ASTModuleListBaseItemNode* ASTModuleListItemNode::getItem() {
    return _item;
}

ASTNodeType ASTModuleListItemNode::getNodeType() {
    return AST_MODULE_LIST_ITEM_NODE;
}

std::string ASTModuleListItemNode::toString() {
    return "MODULE_LIST_ITEM";
}

bool ASTModuleListItemNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTModuleListItemNode*)other;
    return _item->isSameAs(otherNode->getItem());
}

void ASTModuleListItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _item->print();
    Logger::log("----------");
}