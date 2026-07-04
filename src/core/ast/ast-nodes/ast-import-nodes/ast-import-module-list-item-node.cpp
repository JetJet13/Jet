//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-module-list-item-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportModuleListItemNode::ASTImportModuleListItemNode(std::shared_ptr<ASTImportModuleListBaseItemNode> item) {
    _item = item;
    _children.push_back(_item);
}

std::shared_ptr<ASTImportModuleListBaseItemNode> ASTImportModuleListItemNode::getItem() {
    return _item;
}

Position* ASTImportModuleListItemNode::getStartPosition() {
    return _item->getStartPosition();
}

Position* ASTImportModuleListItemNode::getEndPosition() {
    return _item->getEndPosition();
}

ASTNodeType ASTImportModuleListItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_ITEM_NODE;
}

std::string ASTImportModuleListItemNode::toString() {
    return "IMPORT_MODULE_LIST_ITEM";
}

bool ASTImportModuleListItemNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImportModuleListItemNode>(other);
    return _item->isSameAs(otherNode->getItem());
}

void ASTImportModuleListItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _item->print();
    Logger::log("----------");
}

std::string ASTImportModuleListItemNode::toSourceCode() {
    return _item->toSourceCode();
}