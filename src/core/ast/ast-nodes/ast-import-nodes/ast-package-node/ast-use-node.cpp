//
// Created by Johny Georges on 2024-04-13.
//

#include "ast-use-node.h"
#include "../../../../../shared/utils/logger/logger.h"

ASTUseNode::ASTUseNode(Lexeme *lexeme) {
    _lexeme = lexeme;
}

Lexeme* ASTUseNode::getLexeme() {
    return _lexeme;
}

ASTNodeType ASTUseNode::getNodeType() {
    return AST_USE_NODE;
}

std::string ASTUseNode::toString() {
    return "USE";
}

bool ASTUseNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTUseNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTUseNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString());
}