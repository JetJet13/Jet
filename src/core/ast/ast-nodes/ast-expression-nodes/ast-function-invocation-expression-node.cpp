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
// Created by Johny Georges on 2024-03-25.
//

#include "ast-function-invocation-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTFunctionInvocationExpressionNode::ASTFunctionInvocationExpressionNode(std::shared_ptr<ASTExpressionNode> function, std::shared_ptr<ASTFunctionArgumentListNode> arguments) {
    _function = function;
    _arguments = arguments;
    _children.push_back(_function);
    _children.push_back(_arguments);
}

std::shared_ptr<ASTFunctionArgumentListNode> ASTFunctionInvocationExpressionNode::getArguments() {
    return _arguments;
}

std::shared_ptr<ASTExpressionNode> ASTFunctionInvocationExpressionNode::getFunction() {
    return _function;
}

uint64_t ASTFunctionInvocationExpressionNode::numArguments() {
    return _arguments->numArguments();
}

void ASTFunctionInvocationExpressionNode::setTypeSignature(std::shared_ptr<FunctionInvocationTypeSignature> functionInvocationTypeSignature) {
    _typeSignature = functionInvocationTypeSignature;
}

std::shared_ptr<FunctionInvocationTypeSignature> ASTFunctionInvocationExpressionNode::getInvocationTypeSignature() {
    return std::dynamic_pointer_cast<FunctionInvocationTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTFunctionInvocationExpressionNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTFunctionInvocationExpressionNode::getStartPosition() {
    return _function->getStartPosition();
}

std::shared_ptr<Position> ASTFunctionInvocationExpressionNode::getEndPosition() {
    return _arguments->getEndPosition();
}

ASTNodeType ASTFunctionInvocationExpressionNode::getNodeType() {
    return AST_FUNCTION_INVOCATION_EXPRESSION_NODE;
}

std::string ASTFunctionInvocationExpressionNode::toString() {
    return "FUNCTION_INVOCATION_EXPRESSION";
}

bool ASTFunctionInvocationExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTFunctionInvocationExpressionNode>(other);

    return  this->getFunction()->isSameAs(otherNode->getFunction()) &&
            this->getArguments()->isSameAs(otherNode->getArguments());
}

void ASTFunctionInvocationExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _function->print();
    _arguments->print();
    Logger::log("----------");
}

std::string ASTFunctionInvocationExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_function)
    ->add(_arguments);
    return sourceCodeBuilder.build();
}