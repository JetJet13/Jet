//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-float-literal-node.h"

ASTFloatLiteralNode::ASTFloatLiteralNode(Lexeme* floatLiteral) {
    _floatLiteral = floatLiteral;
}

ASTNodeType ASTFloatLiteralNode::getNodeType() {
    return AST_FLOAT_LITERAL_NODE;
}