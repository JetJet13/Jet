//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-identifier-node.h"
#include "../../../shared/utils/logger/logger.h"
#include "ast-control-flow-nodes/try-catch-finally/ast-catch-error-variable-node.h"

ASTIdentifierNode::ASTIdentifierNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

ASTIdentifierNode::ASTIdentifierNode(Lexeme* lexeme, std::string id) {
    _lexeme = lexeme;
    this->setId(id);
}

Lexeme* ASTIdentifierNode::getLexeme() {
    return _lexeme;
}

std::string ASTIdentifierNode::getValue(TokenTable* tokenTable) {
    return tokenTable->getIdentifier(
            _lexeme->getToken()->getValueId().value()
    );
}

ASTNodeType ASTIdentifierNode::getNodeType() {
    return AST_IDENTIFIER_NODE;
}

std::string ASTIdentifierNode::toString() {
    return "IDENTIFIER";
}

Position* ASTIdentifierNode::getStartPosition() {
    return _lexeme->getStartPosition();
}

Position* ASTIdentifierNode::getEndPosition() {
    return _lexeme->getEndPosition();
}

bool ASTIdentifierNode::isSameAs(ASTNode* other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTIdentifierNode*)other;
    return this->getLexeme()->hasSameSymbolTypeAs(otherNode->getLexeme());
}

void ASTIdentifierNode::print() {
    Logger::log(this->toString(), "-", _lexeme->toString(), "|", "id:", _id);
}

std::string ASTIdentifierNode::toSourceCode() {
    return this->getId();
}