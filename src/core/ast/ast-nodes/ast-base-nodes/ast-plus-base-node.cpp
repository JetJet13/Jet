//
// Created by Johny Georges on 2024-03-04.
//

#include "ast-plus-base-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../ast-operator-nodes/ast-unary-operators/ast-unary-operator-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-arithmetic-operator-node.h"

ASTPlusBaseNode::ASTPlusBaseNode(Lexeme* lexeme) {
    _lexeme = lexeme;
}

std::shared_ptr<ASTNode> ASTPlusBaseNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (!prevNode && !nextNode) {
        return shared_from_this();
    }

    std::vector<ASTNodeType> plusOperatorPrevNodes = {
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
    if (prevNode && prevNode.value()->isOneOf(plusOperatorPrevNodes)) {
        Logger::log("transforming PLUS_BASE to BINARY_OPERATOR because prevNode is", prevNode.value()->toString());
        return std::make_shared<ASTBinaryArithmeticOperatorNode>(_lexeme);
    }

    return std::make_shared<ASTUnaryOperatorNode>(_lexeme);
}

ASTNodeType ASTPlusBaseNode::getNodeType() {
    return AST_PLUS_BASE_NODE;
}

std::string ASTPlusBaseNode::toString() {
    return "PLUS_BASE";
}
