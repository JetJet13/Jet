//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-char-literal-node.h"

ASTNodeType ASTCharLiteralNode::getNodeType() {
    return AST_CHAR_LITERAL_NODE;
}

std::string ASTCharLiteralNode::toString() {
    return "CHAR_LITERAL - " + _lexeme->toString();
}

void ASTCharLiteralNode::setValue(TokenTable* tokenTable) {
    _value = tokenTable->getChar(_lexeme->getToken()->getValueId().value());
}

char ASTCharLiteralNode::getValue() {
    return _value;
}

std::string ASTCharLiteralNode::toSourceCode() {
    return "'" +_lexeme->getToken()->getRawValue() + "'";
}