//
// Created by Johny Georges on 2024-04-12.
//

#include "ast-import-spread-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTImportSpreadNode::ASTImportSpreadNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTImportSpreadNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTImportSpreadNode::getNodeType() {
    return AST_IMPORT_SPREAD_NODE;
}

std::string ASTImportSpreadNode::toString() {
    return "IMPORT_SPREAD";
}

bool ASTImportSpreadNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTImportSpreadNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTImportSpreadNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}