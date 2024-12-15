//
// Created by Johny Georges on 2024-03-04.
//

#include "ast-plus-base-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-operator-nodes/ast-unary-operators/ast-unary-operator-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-operator-node.h"

ASTPlusBaseNode::ASTPlusBaseNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

ASTNode * ASTPlusBaseNode::transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) {
    if (!prevNode && !nextNode) {
        return this;
    }

    std::vector<ASTNodeType> plusOperatorPrevNodes = {
            AST_UNARY_EXPRESSION_NODE,
            AST_BINARY_EXPRESSION_NODE,
            AST_LITERAL_EXPRESSION_NODE,
            AST_IDENTIFIER_EXPRESSION_NODE,
            AST_FUNCTION_INVOCATION_EXPRESSION_NODE,
            AST_TUPLE_EXPRESSION_NODE,
            AST_TUPLE_ACCESS_NODE,
            AST_ARRAY_NODE,
            AST_FUNCTION_ARGUMENT_LIST_NODE,
            AST_CLASS_PROPERTY_ACCESS_NODE
    };
    if (prevNode && prevNode.value()->isOneOf(plusOperatorPrevNodes)) {
        Logger::log("transforming PLUS_BASE to BINARY_OPERATOR because prevNode is", prevNode.value()->toString());
        return new ASTBinaryOperatorNode(_lexeme);
    }

    return new ASTUnaryOperatorNode(_lexeme);
}

ASTNodeType ASTPlusBaseNode::getNodeType() {
    return AST_PLUS_BASE_NODE;
}

std::string ASTPlusBaseNode::toString() {
    return "PLUS_BASE";
}
