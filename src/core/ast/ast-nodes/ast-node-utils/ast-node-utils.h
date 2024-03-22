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
            case AST_BLOCK_NODE:
                return true;
            default:
                return false;
        }
    }
};

#endif //JETLANG_AST_NODE_UTILS_H
