//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-import-module-list-wildcard-item-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTImportModuleListWildcardItemNode::ASTImportModuleListWildcardItemNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTImportModuleListWildcardItemNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTImportModuleListWildcardItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_WILDCARD_ITEM_NODE;
}

std::string ASTImportModuleListWildcardItemNode::toString() {
    return "IMPORT_MODULE_LIST_WILDCARD_ITEM";
}

bool ASTImportModuleListWildcardItemNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTImportModuleListWildcardItemNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTImportModuleListWildcardItemNode::print() {
    Logger::log("----------", this->toString(), "----------");
    Logger::log(this->toString(), "-", _lexeme->toString());
    Logger::log("----------");
}

std::string ASTImportModuleListWildcardItemNode::toSourceCode() {
    return _lexeme->getToken()->getSymbol()->toString();
}