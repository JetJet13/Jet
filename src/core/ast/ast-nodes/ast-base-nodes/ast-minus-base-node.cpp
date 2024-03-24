//
// Created by Johny Georges on 2024-03-04.
//

#include "ast-minus-base-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-operator-node.h"
#include "../ast-operator-nodes/ast-unary-operators/ast-unary-operator-node.h"

ASTMinusBaseNode::ASTMinusBaseNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

ASTNode* ASTMinusBaseNode::transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) {
    if (!prevNode && !nextNode) {
        return this;
    }

    std::vector<ASTNodeType> minusOperatorPrevNodes = {
            AST_UNARY_EXPRESSION_NODE,
            AST_BINARY_EXPRESSION_NODE,
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
    };
    if (prevNode && prevNode.value()->isOneOf(minusOperatorPrevNodes)) {
        return new ASTBinaryOperatorNode(_lexeme);
    }

    std::vector<ASTNodeType> unaryMinusOperatorPrevNodes = {
            AST_VARIABLE_INIT_NODE,
            AST_BINARY_OPERATOR_NODE
    };
    std::vector<ASTNodeType> unaryMinusOperatorNextNodes = {
            AST_BINARY_EXPRESSION_NODE,
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
    };
    if ((prevNode && prevNode.value()->isOneOf(unaryMinusOperatorPrevNodes)) ||
        (nextNode && nextNode.value()->isOneOf(unaryMinusOperatorNextNodes))) {
        return new ASTUnaryOperatorNode(_lexeme);
    }

    return this;
}

ASTNodeType ASTMinusBaseNode::getNodeType() {
    return AST_MINUS_BASE_NODE;
}

std::string ASTMinusBaseNode::toString() {
    return "MINUS_BASE";
}