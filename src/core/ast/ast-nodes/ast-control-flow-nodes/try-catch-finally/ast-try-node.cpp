//
// Created by Johny Georges on 2024-04-01.
//

#include "ast-try-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTTryNode::ASTTryNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTTryNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTTryNode::getNodeType() {
    return AST_TRY_NODE;
}

std::string ASTTryNode::toString() {
    return "TRY";
}

bool ASTTryNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTTryNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTTryNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}