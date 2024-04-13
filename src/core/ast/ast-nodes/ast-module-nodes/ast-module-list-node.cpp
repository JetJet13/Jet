//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTModuleListNode::ASTModuleListNode() {
    _items = std::vector<ASTModuleListItemNode*>();
}

ASTModuleListNode::ASTModuleListNode(std::vector<ASTModuleListItemNode*> items) {
    _items = std::vector<ASTModuleListItemNode*>();
    for (auto item: items) {
        _items.push_back(item);
    }
}

std::vector<ASTModuleListItemNode*> ASTModuleListNode::getItems() {
    return _items;
}

unsigned long ASTModuleListNode::numItems() {
    return _items.size();
}

ASTModuleListNode* ASTModuleListNode::addEnumKeyValue(ASTModuleListItemNode* item) {
    _items.push_back(item);
    return this;
}

ASTNodeType ASTModuleListNode::getNodeType() {
    return AST_MODULE_LIST_NODE;
}

std::string ASTModuleListNode::toString() {
    return "MODULE_LIST";
}

bool ASTModuleListNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTModuleListNode*)other;
    auto otherNodeElements = otherNode->getItems();
    if (this->numItems() != otherNode->numItems()) {
        return false;
    }
    for (int i = 0; i < this->numItems(); i++) {
        if (!_items[i]->isSameAs(otherNodeElements[i])) {
            return false;
        }
    }

    return true;
}

void ASTModuleListNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto item : _items) {
        item->print();
    }
    Logger::log("----------");
}