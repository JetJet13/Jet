//
// Created by Johny Georges on 2024-03-29.
//

#include "ast-skip-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTSkipNode::ASTSkipNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTSkipNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTSkipNode::getNodeType() {
    return AST_SKIP_NODE;
}

std::string ASTSkipNode::toString() {
    return "SKIP";
}

bool ASTSkipNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTSkipNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTSkipNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}