//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTModuleListNode::ASTModuleListNode(std::shared_ptr<ASTModuleListStartNode> moduleListStartNode, std::shared_ptr<ASTModuleListEndNode> moduleListEndNode) {
    _moduleListStartNode = moduleListStartNode;
    _moduleListEndNode = moduleListEndNode;
    _children.push_back(_moduleListStartNode);
    _children.push_back(_moduleListEndNode);
    _items = std::vector<std::shared_ptr<ASTModuleListItemNode>>();
}

ASTModuleListNode::ASTModuleListNode(std::shared_ptr<ASTModuleListStartNode> moduleListStartNode, std::vector<std::shared_ptr<ASTModuleListItemNode>> items, std::shared_ptr<ASTModuleListEndNode> moduleListEndNode) {
    _moduleListStartNode = moduleListStartNode;
    _moduleListEndNode = moduleListEndNode;
    _children.push_back(_moduleListStartNode);
    _children.push_back(_moduleListEndNode);
    _items = std::vector<std::shared_ptr<ASTModuleListItemNode>>();
    for (auto item: items) {
        this->addItem(item);
    }
}

std::vector<std::shared_ptr<ASTModuleListItemNode>> ASTModuleListNode::getItems() {
    return _items;
}

uint64_t ASTModuleListNode::numItems() {
    return _items.size();
}

std::shared_ptr<ASTModuleListNode> ASTModuleListNode::addItem(std::shared_ptr<ASTModuleListItemNode> item) {
    _items.push_back(item);
    _children.push_back(item);
    return std::dynamic_pointer_cast<ASTModuleListNode>(shared_from_this());
}

std::shared_ptr<Position> ASTModuleListNode::getStartPosition() {
    return _moduleListStartNode->getStartPosition();
}

std::shared_ptr<Position> ASTModuleListNode::getEndPosition() {
    return _moduleListEndNode->getEndPosition();
}

ASTNodeType ASTModuleListNode::getNodeType() {
    return AST_MODULE_LIST_NODE;
}

std::string ASTModuleListNode::toString() {
    return "MODULE_LIST";
}

bool ASTModuleListNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTModuleListNode>(other);
    auto otherNodeElements = otherNode->getItems();
    if (this->numItems() != otherNode->numItems()) {
        return false;
    }
    for (uint64_t i = 0; i < this->numItems(); i++) {
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