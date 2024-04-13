//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-module-list-spread-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTModuleListSpreadItemNode::ASTModuleListSpreadItemNode(ASTIdentifierNode* identifier) {
    _identifier = identifier;
}

ASTIdentifierNode* ASTModuleListSpreadItemNode::getIdentifier() {
    return _identifier;
}

ASTNodeType ASTModuleListSpreadItemNode::getNodeType() {
    return AST_MODULE_LIST_SPREAD_ITEM_NODE;
}

std::string ASTModuleListSpreadItemNode::toString() {
    return "MODULE_LIST_SPREAD_ITEM";
}

bool ASTModuleListSpreadItemNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTModuleListSpreadItemNode*)other;
    return this->getIdentifier()->isSameAs(otherNode->getIdentifier());
}

void ASTModuleListSpreadItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _identifier->print();
    Logger::log("----------");
}