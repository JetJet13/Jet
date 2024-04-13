//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-module-list-end-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportModuleListEndNode::ASTImportModuleListEndNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTImportModuleListEndNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTImportModuleListEndNode::getNodeType() {
    return AST_IMPORT_MODULE_LIST_END_NODE;
}

std::string ASTImportModuleListEndNode::toString() {
    return "IMPORT_MODULE_LIST_END";
}

bool ASTImportModuleListEndNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTImportModuleListEndNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTImportModuleListEndNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}