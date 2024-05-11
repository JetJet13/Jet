//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-module-list-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportModuleListNode::ASTImportModuleListNode() {
    _items = std::vector<ASTImportModuleListItemNode*>();
}

ASTImportModuleListNode::ASTImportModuleListNode(std::vector<ASTImportModuleListItemNode*> items) {
    _items = std::vector<ASTImportModuleListItemNode*>();
    for (auto item: items) {
        this->addItem(item);
    }
}

std::vector<ASTImportModuleListItemNode*> ASTImportModuleListNode::getItems() {
    return _items;
}

unsigned long ASTImportModuleListNode::numItems() {
    return _items.size();
}

ASTImportModuleListNode* ASTImportModuleListNode::addItem(ASTImportModuleListItemNode* item) {
    _items.push_back(item);
    _children.push_back(item);
    return this;
}

ASTNodeType ASTImportModuleListNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_NODE;
}

std::string ASTImportModuleListNode::toString() {
    return "IMPORT_MODULE_LIST";
}

bool ASTImportModuleListNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTImportModuleListNode*)other;
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

void ASTImportModuleListNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto item : _items) {
        item->print();
    }
    Logger::log("----------");
}