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

Position* ASTImportModuleListWildcardItemNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

Position* ASTImportModuleListWildcardItemNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

ASTNodeType ASTImportModuleListWildcardItemNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_WILDCARD_ITEM_NODE;
}

std::string ASTImportModuleListWildcardItemNode::toString() {
    return "IMPORT_MODULE_LIST_WILDCARD_ITEM";
}

bool ASTImportModuleListWildcardItemNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTImportModuleListWildcardItemNode>(other);
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