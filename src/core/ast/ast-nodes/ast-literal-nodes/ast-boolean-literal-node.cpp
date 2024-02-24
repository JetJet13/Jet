//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-boolean-literal-node.h"

ASTBooleanLiteralNode::ASTBooleanLiteralNode(Lexeme* booleanLiteral) {
    _booleanLiteral = booleanLiteral;
}

ASTNodeType ASTBooleanLiteralNode::getNodeType() {
    return AST_BOOLEAN_LITERAL_NODE;
}

std::string ASTBooleanLiteralNode::toString() {
    return "BOOLEAN_LITERAL";
}
