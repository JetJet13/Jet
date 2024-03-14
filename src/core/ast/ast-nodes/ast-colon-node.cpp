//
// Created by Johny Georges on 2024-03-14.
//

#include "ast-colon-node.h"
#include "../../../shared/utils/logger/logger.h"

ASTColonNode::ASTColonNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTColonNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTColonNode::getNodeType() {
    return AST_COLON_NODE;
}

std::string ASTColonNode::toString() {
    return "COLON";
}

bool ASTColonNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTColonNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTColonNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}