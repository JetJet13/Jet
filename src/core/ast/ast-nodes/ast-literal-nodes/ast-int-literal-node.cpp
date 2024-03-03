//
// Created by Johny Georges on 2024-01-13.
//

#include "ast-int-literal-node.h"

ASTNodeType ASTIntLiteralNode::getNodeType() {
    return AST_INT_LITERAL_NODE;
}

std::string ASTIntLiteralNode::toString() {
    return "INT_LITERAL - " + _lexemeLiteral->toString();
}
