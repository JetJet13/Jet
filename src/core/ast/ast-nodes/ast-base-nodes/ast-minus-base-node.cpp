//
// Created by Johny Georges on 2024-03-04.
//

#include "ast-minus-base-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-arithmetic-operator-node.h"
#include "../ast-operator-nodes/ast-unary-operators/ast-unary-operator-node.h"

ASTMinusBaseNode::ASTMinusBaseNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

ASTNode * ASTMinusBaseNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {
    if (!prevNode && !nextNode) {
        return this;
    }

    std::vector<ASTNodeType> minusOperatorPrevNodes = {
            AST_UNARY_EXPRESSION_NODE,
            AST_BINARY_ARITHMETIC_EXPRESSION_NODE,
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_INVOCATION_EXPRESSION_NODE,
            AST_OBJECT_ACCESS_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_EXPRESSION_NODE,
            AST_ARRAY_ACCESS_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_NODE,
            AST_ARRAY_NODE,
            AST_FUNCTION_ARGUMENT_LIST_NODE,
            AST_CLASS_PROPERTY_ACCESS_NODE
    };
    if (prevNode && prevNode.value()->isOneOf(minusOperatorPrevNodes)) {
        return new ASTBinaryArithmeticOperatorNode(_lexeme);
    }

    return new ASTUnaryOperatorNode(_lexeme);
}

ASTNodeType ASTMinusBaseNode::getNodeType() {
    return AST_MINUS_BASE_NODE;
}

std::string ASTMinusBaseNode::toString() {
    return "MINUS_BASE";
}