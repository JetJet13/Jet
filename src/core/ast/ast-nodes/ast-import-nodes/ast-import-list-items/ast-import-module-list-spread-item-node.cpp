//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-module-list-spread-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTImportModuleListSpreadItemNode::ASTImportModuleListSpreadItemNode(ASTIdentifierNode* identifier) {
    _identifier = identifier;
}

ASTIdentifierNode* ASTImportModuleListSpreadItemNode::getIdentifier() {
    return _identifier;
}

ASTNodeType ASTImportModuleListSpreadItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_SPREAD_ITEM_NODE;
}

std::string ASTImportModuleListSpreadItemNode::toString() {
    return "IMPORT_MODULE_LIST_SPREAD_ITEM";
}

bool ASTImportModuleListSpreadItemNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTImportModuleListSpreadItemNode*)other;
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier());
}

void ASTImportModuleListSpreadItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}