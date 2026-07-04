//
// Created by Johny Georges on 2024-05-20.
//

#include "ast-literal-node-value-assignor.h"
#include <any>

void ASTLiteralNodeValueAssignor::assignValue(std::shared_ptr<ASTNode> node, std::shared_ptr<TokenTable> tokenTable) {
    if (node->isOneOf({
        AST_INT_LITERAL_NODE,
        AST_FLOAT_LITERAL_NODE,
        AST_CHAR_LITERAL_NODE,
        AST_STRING_LITERAL_NODE,
        AST_BOOLEAN_LITERAL_NODE })) {
        (std::dynamic_pointer_cast<ASTLiteralNode>(node))->setValue(tokenTable);
    }
}