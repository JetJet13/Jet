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
// Created by Johny Georges on 2024-04-26.
//

#include "ast-new-class-instance-expression.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTNewClassInstanceExpressionNode::ASTNewClassInstanceExpressionNode(std::shared_ptr<ASTNewNode> newKeywordNode, std::shared_ptr<ASTClassNameNode> className, std::shared_ptr<ASTFunctionArgumentListNode> arguments) {
    _new = newKeywordNode;
    _className = className;
    _arguments = arguments;
    _children.push_back(_new);
    _children.push_back(_className.value());
    _children.push_back(_arguments);
}

ASTNewClassInstanceExpressionNode::ASTNewClassInstanceExpressionNode(std::shared_ptr<ASTNewNode> newKeywordNode, std::shared_ptr<ASTModuleAccessExpressionNode> moduleAccessExpressionNode, std::shared_ptr<ASTFunctionArgumentListNode> arguments) {
    _new = newKeywordNode;
    _moduleAccessExpression = moduleAccessExpressionNode;
    _arguments = arguments;
    _children.push_back(_new);
    _children.push_back(_moduleAccessExpression.value());
    _children.push_back(_arguments);
}

std::shared_ptr<ASTFunctionArgumentListNode> ASTNewClassInstanceExpressionNode::getArguments() {
    return _arguments;
}

std::string ASTNewClassInstanceExpressionNode::getClassName() {
    if (_className) {
        return _className.value()->getId();
    }
    return _moduleAccessExpression.value()->getTarget()->getTarget()->getId();
}

std::optional<std::string> ASTNewClassInstanceExpressionNode::getModuleName() {
    if (_moduleAccessExpression) {
        return _moduleAccessExpression.value()->getSource()->getSource()->getIdentifierNode()->getId();
    }
    return {};
}

uint64_t ASTNewClassInstanceExpressionNode::numArguments() {
    return _arguments->numArguments();
}

std::shared_ptr<TypeSignature> ASTNewClassInstanceExpressionNode::getTypeSignature() {
    return _typeSignature;
}

void ASTNewClassInstanceExpressionNode::setTypeSignature(std::shared_ptr<NewClassInstanceTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<NewClassInstanceTypeSignature> ASTNewClassInstanceExpressionNode::getClassInstanceTypeSignature() {
    return std::dynamic_pointer_cast<NewClassInstanceTypeSignature>(_typeSignature);
}

std::shared_ptr<Position> ASTNewClassInstanceExpressionNode::getStartPosition() {
    return _new->getStartPosition();
}

std::shared_ptr<Position> ASTNewClassInstanceExpressionNode::getEndPosition() {
    return _arguments->getEndPosition();
}

ASTNodeType ASTNewClassInstanceExpressionNode::getNodeType() {
    return AST_NEW_CLASS_INSTANCE_EXPRESSION_NODE;
}

std::string ASTNewClassInstanceExpressionNode::toString() {
    return "NEW_CLASS_INSTANCE_EXPRESSION";
}

bool ASTNewClassInstanceExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTNewClassInstanceExpressionNode>(other);

    return this->getClassName() == otherNode->getClassName() &&
           this->getArguments()->isSameAs(otherNode->getArguments());
}

void ASTNewClassInstanceExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    if (_className) {
        _className.value()->print();
    }
    if (_moduleAccessExpression) {
        _moduleAccessExpression.value()->print();
    }
    _arguments->print();
    Logger::log("----------");
}

std::string ASTNewClassInstanceExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_new);
    if (_className) {
        sourceCodeBuilder.add(_className.value());
    }
    if (_moduleAccessExpression) {
        sourceCodeBuilder.add(_moduleAccessExpression.value());
    }
    sourceCodeBuilder.add(_arguments);
    return sourceCodeBuilder.build();
}