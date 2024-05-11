//
// Created by Johny Georges on 2024-03-26.
//

#include "ast-tuple-list-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTTupleListNode::ASTTupleListNode() {
    _items = std::vector<ASTTupleItemNode*>();
}

ASTTupleListNode::ASTTupleListNode(std::vector<ASTTupleItemNode*> items) {
    _items = std::vector<ASTTupleItemNode*>();
    for (auto item: items) {
        this->addItem(item);
    }
}

std::vector<ASTTupleItemNode*> ASTTupleListNode::getItems() {
    return _items;
}

unsigned long ASTTupleListNode::numItems() {
    return _items.size();
}

ASTTupleListNode* ASTTupleListNode::addItem(ASTTupleItemNode* item) {
    _items.push_back(item);
    _children.push_back(item);
    return this;
}

ASTNodeType ASTTupleListNode::getNodeType() {
    return AST_TUPLE_LIST_NODE;
}

std::string ASTTupleListNode::toString() {
    return "TUPLE_LIST";
}

bool ASTTupleListNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTTupleListNode*)other;
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

void ASTTupleListNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto item : _items) {
        item->print();
    }
    Logger::log("----------");
}