//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTModuleListNode::ASTModuleListNode(ASTModuleListStartNode* moduleListStartNode, ASTModuleListEndNode* moduleListEndNode) {
    _moduleListStartNode = moduleListStartNode;
    _moduleListEndNode = moduleListEndNode;
    _children.push_back(_moduleListStartNode);
    _children.push_back(_moduleListEndNode);
    _items = std::vector<ASTModuleListItemNode*>();
}

ASTModuleListNode::ASTModuleListNode(ASTModuleListStartNode* moduleListStartNode, std::vector<ASTModuleListItemNode*> items, ASTModuleListEndNode* moduleListEndNode) {
    _moduleListStartNode = moduleListStartNode;
    _moduleListEndNode = moduleListEndNode;
    _children.push_back(_moduleListStartNode);
    _children.push_back(_moduleListEndNode);
    _items = std::vector<ASTModuleListItemNode*>();
    for (auto item: items) {
        this->addItem(item);
    }
}

std::vector<ASTModuleListItemNode*> ASTModuleListNode::getItems() {
    return _items;
}

unsigned long ASTModuleListNode::numItems() {
    return _items.size();
}

ASTModuleListNode* ASTModuleListNode::addItem(ASTModuleListItemNode* item) {
    _items.push_back(item);
    _children.push_back(item);
    return this;
}

Position* ASTModuleListNode::getStartPosition() {
    return _moduleListStartNode->getStartPosition();
}

Position* ASTModuleListNode::getEndPosition() {
    return _moduleListEndNode->getEndPosition();
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
    for (unsigned long i = 0; i < this->numItems(); i++) {
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

std::string ASTModuleListNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_moduleListStartNode);
    for (auto item : _items) {
        sourceCodeBuilder.add(item);
    }
    sourceCodeBuilder.add(_moduleListEndNode);
    return sourceCodeBuilder.build();
}