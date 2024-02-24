//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-int-literal-node.h"

ASTIntLiteralNode::ASTIntLiteralNode(Lexeme* intLiteral) {
    _intLiteral = intLiteral;
}

ASTNodeType ASTIntLiteralNode::getNodeType() {
    return AST_INT_LITERAL_NODE;
}

std::string ASTIntLiteralNode::toString() {
    return "INT_LITERAL";
}
