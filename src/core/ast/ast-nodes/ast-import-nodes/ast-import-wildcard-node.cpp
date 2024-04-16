//
// Created by Johny Georges on 2024-04-15.
//

#include "ast-import-wildcard-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportWildcardNode::ASTImportWildcardNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTImportWildcardNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTImportWildcardNode::getNodeType() {
    return AST_IMPORT_WILDCARD_NODE;
}

std::string ASTImportWildcardNode::toString() {
    return "IMPORT_WILDCARD";
}

bool ASTImportWildcardNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTImportWildcardNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTImportWildcardNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}