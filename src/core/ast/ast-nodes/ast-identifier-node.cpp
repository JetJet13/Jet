//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-identifier-node.h"
#include "../../../shared/utils/logger/logger.h"

ASTIdentifierNode::ASTIdentifierNode(Lexeme *lexeme) {
    _identifier = lexeme;
}

Lexeme* ASTIdentifierNode::getIdentifier() {
    return _identifier;
}

ASTNodeType ASTIdentifierNode::getNodeType() {
    return AST_IDENTIFIER_NODE;
}

std::string ASTIdentifierNode::toString() {
    return "IDENTIFIER";
}

bool ASTIdentifierNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTIdentifierNode*)other;
    return this->getIdentifier()->hasSameSymbolTypeAs(otherNode->getIdentifier());
}

void ASTIdentifierNode::print() {
    Logger::log(this->toString(), "-", _identifier->toString());
}