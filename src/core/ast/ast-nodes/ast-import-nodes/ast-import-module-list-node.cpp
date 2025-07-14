//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-module-list-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTImportModuleListNode::ASTImportModuleListNode(ASTImportModuleListStartNode* importModuleListStartNode, ASTImportModuleListEndNode* importModuleListEndNode) {
    _importModuleListStartNode = importModuleListStartNode;
    _importModuleListEndNode = importModuleListEndNode;
    _children.push_back(_importModuleListStartNode);
    _children.push_back(_importModuleListEndNode);
    _items = std::vector<ASTImportModuleListItemNode*>();
}

ASTImportModuleListNode::ASTImportModuleListNode(ASTImportModuleListStartNode* importModuleListStartNode, std::vector<ASTImportModuleListItemNode*> items, ASTImportModuleListEndNode* importModuleListEndNode) {
    _importModuleListStartNode = importModuleListStartNode;
    _importModuleListEndNode = importModuleListEndNode;
    _children.push_back(_importModuleListStartNode);
    _children.push_back(_importModuleListEndNode);
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

Position* ASTImportModuleListNode::getStartPosition() {
    return _importModuleListStartNode->getStartPosition();
}

Position* ASTImportModuleListNode::getEndPosition() {
    return _importModuleListEndNode->getEndPosition();
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

std::string ASTImportModuleListNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_importModuleListStartNode);
    for (auto item : _items) {
        sourceCodeBuilder.add(item);
    }
    sourceCodeBuilder.add(_importModuleListEndNode);
    return sourceCodeBuilder.build();
}