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
// Created by Johny Georges on 2024-01-12.
//

#include "ast-expression-node.h"
#include "../ast-function-nodes/ast-function-argument-node.h"
#include "../ast-tuple-nodes/ast-tuple-item-node.h"


void ASTExpressionNode::setTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::string ASTExpressionNode::getModuleId() {
    return "";
}

std::shared_ptr<TypeSignature> ASTExpressionNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<ASTNode> ASTExpressionNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    return this->baseTransformIfNecessary(prevNode, nextNode, mode);
}

bool ASTExpressionNode::isExpression() {
    return true;
}

ASTNodeType ASTExpressionNode::getNodeType() {
    return AST_EXPRESSION_NODE;
}

std::string ASTExpressionNode::toString() {
    return "EXPRESSION";
}

bool ASTExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    return other->is(this->getNodeType());
}

std::shared_ptr<ASTNode> ASTExpressionNode::baseTransformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    if (prevNode && prevNode.value()->isOneOf({AST_COMMA_NODE, AST_FUNCTION_ARGUMENT_LIST_START_NODE }) &&
        nextNode && nextNode.value()->isOneOf({AST_COMMA_NODE, AST_FUNCTION_ARGUMENT_LIST_END_NODE }) &&
        mode == SA_FUNCTION_ARGUMENT_LIST_MODE) {
        return std::make_shared<ASTFunctionArgumentNode>(std::dynamic_pointer_cast<ASTExpressionNode>(shared_from_this()));
    }

    if (prevNode && prevNode.value()->isOneOf({AST_COMMA_NODE, AST_TUPLE_LIST_START_NODE }) &&
        nextNode && nextNode.value()->isOneOf({AST_COMMA_NODE, AST_TUPLE_LIST_END_NODE }) &&
        mode == SA_TUPLE_LIST_MODE) {
        return std::make_shared<ASTTupleItemNode>(std::dynamic_pointer_cast<ASTExpressionNode>(shared_from_this()));
    }

    return shared_from_this();
}