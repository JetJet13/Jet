//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-module-list-start-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportModuleListStartNode::ASTImportModuleListStartNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTImportModuleListStartNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTImportModuleListStartNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_START_NODE;
}

std::string ASTImportModuleListStartNode::toString() {
    return "IMPORT_MODULE_LIST_START";
}

bool ASTImportModuleListStartNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTImportModuleListStartNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTImportModuleListStartNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}