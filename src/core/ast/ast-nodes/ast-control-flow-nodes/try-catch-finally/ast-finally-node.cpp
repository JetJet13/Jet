//
// Created by Johny Georges on 2024-04-01.
//

#include "ast-finally-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTFinallyNode::ASTFinallyNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTFinallyNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTFinallyNode::getNodeType() {
    return AST_FINALLY_NODE;
}

std::string ASTFinallyNode::toString() {
    return "FINALLY";
}

bool ASTFinallyNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTFinallyNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTFinallyNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}