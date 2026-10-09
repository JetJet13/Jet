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
// Created by Johny Georges on 2024-03-19.
//

#include "ast-function-return-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionReturnExpressionNode::ASTFunctionReturnExpressionNode(std::shared_ptr<ASTFunctionReturnNode> returnNode) {
    _returnNode = returnNode;
    _returnExpression = {};
}

ASTFunctionReturnExpressionNode::ASTFunctionReturnExpressionNode(std::shared_ptr<ASTFunctionReturnNode> returnNode, std::shared_ptr<ASTExpressionNode> expressionNode) {
    _returnNode = returnNode;
    _returnExpression = expressionNode;
    _children.push_back(_returnExpression.value());
}

std::shared_ptr<ASTFunctionReturnNode> ASTFunctionReturnExpressionNode::getReturnNode() {
    return _returnNode;
}

bool ASTFunctionReturnExpressionNode::hasExpression() {
    return _returnExpression.has_value();
}

std::optional<std::shared_ptr<ASTExpressionNode>> ASTFunctionReturnExpressionNode::getExpression() {
    return _returnExpression;
}

std::shared_ptr<Position> ASTFunctionReturnExpressionNode::getStartPosition() {
    return _returnNode->getStartPosition();
}

std::shared_ptr<Position> ASTFunctionReturnExpressionNode::getEndPosition() {
    if (_returnExpression) {
        return _returnExpression.value()->getEndPosition();
    }
    return _returnNode->getEndPosition();
}

ASTNodeType ASTFunctionReturnExpressionNode::getNodeType() {
    return AST_FUNCTION_RETURN_EXPRESSION_NODE;
}

std::string ASTFunctionReturnExpressionNode::toString() {
    return "FUNCTION_RETURN_EXPRESSION";
}

bool ASTFunctionReturnExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTFunctionReturnExpressionNode>(other);
    if (this->getExpression() && otherNode->getExpression()) {
        auto result = this->getExpression().value()->isSameAs(otherNode->getExpression().value());
        return this->getExpression().value()->isSameAs(otherNode->getExpression().value());
    } else if (!this->getExpression() && !otherNode->getExpression()) {
        return true;
    } else {
        return false;
    }
}

void ASTFunctionReturnExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    if (_returnExpression) {
        _returnExpression.value()->print();
    } else {
        _returnNode->print();
    }
    Logger::log("----------");
}

std::string ASTFunctionReturnExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_returnNode);
    if (_returnExpression) {
        sourceCodeBuilder.add(_returnExpression.value());
    }
    return sourceCodeBuilder.build();
}