//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-float-literal-node.h"

ASTNodeType ASTFloatLiteralNode::getNodeType() {
    return AST_FLOAT_LITERAL_NODE;
}

std::string ASTFloatLiteralNode::toString() {
    return "FLOAT_LITERAL - " + _lexeme->toString();
}

void ASTFloatLiteralNode::setValue(TokenTable* tokenTable) {
    _value = tokenTable->getFloat(_lexeme->getToken()->getValueId().value());
}

std::string ASTFloatLiteralNode::getValue() {
    return _value;
}