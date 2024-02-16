//
// Created by Johny Georges on 2024-02-10.
//

#ifndef JETLANG_AST_NODE_UTILS_H
#define JETLANG_AST_NODE_UTILS_H

#include "../ast-node.h"

namespace ASTNodeUtils {
    bool isLiteralNode(ASTNode* node) {
        switch (node->getNodeType()) {
            case AST_BOOLEAN_LITERAL_NODE:
            case AST_CHAR_LITERAL_NODE:
            case AST_FLOAT_LITERAL_NODE:
            case AST_INT_LITERAL_NODE:
            case AST_STRING_LITERAL_NODE:
                return true;
            default:
                return false;
        }
    }
    bool isTerminatorNode(ASTNode* node) {
        return node->getNodeType() == AST_TERMINATOR_NODE;
    }
    bool isBinaryOperatorNode(ASTNode* node) {
        switch (node->getNodeType()) {
            case AST_LOGICAL_OPERATOR_NODE:
            case AST_BINARY_OPERATOR_NODE:
                return true;
            default:
                return false;
        }
    }

};

#endif //JETLANG_AST_NODE_UTILS_H
