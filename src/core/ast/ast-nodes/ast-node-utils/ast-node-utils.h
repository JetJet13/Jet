//
// Created by Johny Georges on 2024-02-10.
//

#ifndef JETLANG_AST_NODE_UTILS_H
#define JETLANG_AST_NODE_UTILS_H

#include "../ast-node.h"

namespace ASTNodeUtils {
    static bool isDeclarationNode(ASTNode* node) {
        switch (node->getNodeType()) {
            case AST_VARIABLE_DECLARATION_NODE:
            case AST_FUNCTION_RETURN_EXPRESSION_NODE:
            case AST_FUNCTION_DECLARATION_NODE:
            case AST_PROCEDURE_DECLARATION_NODE:
            case AST_VARIABLE_ASSIGNMENT_STATEMENT_NODE:
            case AST_IF_STATEMENT_NODE:
            case AST_WHILE_STATEMENT_NODE:
            case AST_FOR_STATEMENT_NODE:
            case AST_EXPRESSION_STATEMENT_NODE:
            case AST_ENUM_DECLARATION_NODE:
            case AST_BLOCK_NODE:
                return true;
            default:
                return false;
        }
    }

    static bool isExpressionNode(ASTNode* node) {
        switch (node->getNodeType()) {
            case AST_IDENTIFIER_EXPRESSION_NODE:
            case AST_LITERAL_EXPRESSION_NODE:
            case AST_BINARY_EXPRESSION_NODE:
            case AST_LOGICAL_EXPRESSION_NODE:
            case AST_UNARY_EXPRESSION_NODE:
            case AST_OBJECT_ACCESS_EXPRESSION_NODE:
            case AST_FUNCTION_INVOCATION_EXPRESSION_NODE:
            case AST_FUNCTION_RETURN_EXPRESSION_NODE:
            case AST_ARRAY_ACCESS_EXPRESSION_NODE:
            case AST_ARRAY_EXPRESSION_NODE:
            case AST_STRUCT_EXPRESSION_NODE:
            case AST_TUPLE_ACCESS_EXPRESSION_NODE:
            case AST_TUPLE_EXPRESSION_NODE:
                return true;
            default:
                return false;
        }
    }
};

#endif //JETLANG_AST_NODE_UTILS_H
