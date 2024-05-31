//
// Created by Johny Georges on 2024-04-18.
//

#include "ast-symbol-node.h"
#include "../../../shared/utils/logger/logger.h"

ASTSymbolNode::ASTSymbolNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

ASTSymbolNode::ASTSymbolNode(Lexeme *lexeme, std::string id) {
    _lexeme = lexeme;
    this->setId(id);
}

Lexeme* ASTSymbolNode::getLexeme() {
    return _lexeme;
}


bool ASTSymbolNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTSymbolNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTSymbolNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString(), "|", "id:", _id);
}

std::string ASTSymbolNode::toSourceCode() {
    return this->getLexeme()->getToken()->getSymbol()->toString();
}