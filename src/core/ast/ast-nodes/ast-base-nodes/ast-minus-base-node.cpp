// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2024-03-04.
//

#include "ast-minus-base-node.h"
#include "../ast-operator-nodes/ast-binary-operators/ast-binary-arithmetic-operator-node.h"
#include "../ast-operator-nodes/ast-unary-operators/ast-unary-operator-node.h"

ASTMinusBaseNode::ASTMinusBaseNode(std::shared_ptr<Lexeme> lexeme) {
    _lexeme = lexeme;
}

std::shared_ptr<ASTNode> ASTMinusBaseNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (!prevNode && !nextNode) {
        return shared_from_this();
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
        return std::make_shared<ASTBinaryArithmeticOperatorNode>(_lexeme);
    }

    return std::make_shared<ASTUnaryOperatorNode>(_lexeme);
}

ASTNodeType ASTMinusBaseNode::getNodeType() {
    return AST_MINUS_BASE_NODE;
}

std::string ASTMinusBaseNode::toString() {
    return "MINUS_BASE";
}