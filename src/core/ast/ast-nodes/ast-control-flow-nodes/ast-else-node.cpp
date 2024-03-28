//
// Created by Johny Georges on 2024-03-28.
//

#include "ast-else-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTElseNode::ASTElseNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTElseNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTElseNode::getNodeType() {
    return AST_ELSE_NODE;
}

std::string ASTElseNode::toString() {
    return "ELSE";
}

bool ASTElseNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTElseNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTElseNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}