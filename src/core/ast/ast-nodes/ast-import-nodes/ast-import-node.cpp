//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportNode::ASTImportNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTImportNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTImportNode::getNodeType() {
    return AST_IMPORT_NODE;
}

std::string ASTImportNode::toString() {
    return "IMPORT";
}

bool ASTImportNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTImportNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTImportNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}