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
// Created by Johny Georges on 2025-06-16.
//

#include "ast-object-access-invocation-expression-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"
#include "../../../type-signature/shared-type-signature/shared-type-signature.h"

ASTObjectAccessInvocationExpressionNode::ASTObjectAccessInvocationExpressionNode(std::shared_ptr<ASTObjectAccessExpressionNode> objectAccess, std::shared_ptr<ASTFunctionArgumentListNode> arguments) {
    _objectAccess = objectAccess;
    _arguments = arguments;
    _children.push_back(_objectAccess);
    _children.push_back(_arguments);
}

std::shared_ptr<ASTFunctionArgumentListNode> ASTObjectAccessInvocationExpressionNode::getArguments() {
    return _arguments;
}

std::shared_ptr<ASTObjectAccessExpressionNode> ASTObjectAccessInvocationExpressionNode::getObjectAccess() {
    return _objectAccess;
}

std::shared_ptr<ASTObjectAccessSourceNode> ASTObjectAccessInvocationExpressionNode::getSource() {
    return _objectAccess->getSource();
}

std::shared_ptr<ASTObjectAccessTargetNode> ASTObjectAccessInvocationExpressionNode::getTarget() {
    return _objectAccess->getTarget();
}

std::shared_ptr<InvocableTypeSignature> ASTObjectAccessInvocationExpressionNode::getInvocableTypeSignature() {
    return std::dynamic_pointer_cast<InvocableTypeSignature>(_objectAccess->getTypeSignature());
}

std::string ASTObjectAccessInvocationExpressionNode::getName() {
    return _objectAccess->getTarget()->getTarget()->getIdentifierNode()->getId();
}

uint64_t ASTObjectAccessInvocationExpressionNode::numArguments() {
    return _arguments->numArguments();
}

bool ASTObjectAccessInvocationExpressionNode::isArrayPrototypeInvocation() {
    auto sourceTypeSignature = this->getSource()->getSource()->getTypeSignature();
    if (sourceTypeSignature->typeTargetIs(SHARED_TYPE_SOURCE)) {
        auto sharedTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature->getTargetTypeSignature());
        sourceTypeSignature = sharedTypeSignature->getUnderlyingType();
    }
    return sourceTypeSignature->typeTargetIs(ARRAY_TYPE_SOURCE)
           && this->getObjectAccess()->getTypeSignature()->isPrototype();
}

bool ASTObjectAccessInvocationExpressionNode::isStringPrototypeInvocation() {
    auto sourceTypeSignature = this->getSource()->getSource()->getTypeSignature();
    if (sourceTypeSignature->typeTargetIs(SHARED_TYPE_SOURCE)) {
        auto sharedTypeSignature = std::dynamic_pointer_cast<SharedTypeSignature>(sourceTypeSignature->getTargetTypeSignature());
        sourceTypeSignature = sharedTypeSignature->getUnderlyingType();
    }
    return sourceTypeSignature->typeTargetIs(STRING_LITERAL_TYPE_SOURCE)
           && this->getObjectAccess()->getTypeSignature()->isPrototype();
}

bool ASTObjectAccessInvocationExpressionNode::isSharedPtrPrototypeInvocation() {
    return this->getSource()->getSource()->getTypeSignature()->typeTargetIs(SHARED_TYPE_SOURCE)
            && this->getObjectAccess()->getTypeSignature()->isPrototype();
}

std::shared_ptr<Position> ASTObjectAccessInvocationExpressionNode::getStartPosition() {
    return _objectAccess->getStartPosition();
}

std::shared_ptr<Position> ASTObjectAccessInvocationExpressionNode::getEndPosition() {
    return _arguments->getEndPosition();
}

ASTNodeType ASTObjectAccessInvocationExpressionNode::getNodeType() {
    return AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE;
}

std::string ASTObjectAccessInvocationExpressionNode::toString() {
    return "AST_OBJECT_ACCESS_INVOCATION_EXPRESSION_NODE";
}

bool ASTObjectAccessInvocationExpressionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTObjectAccessInvocationExpressionNode>(other);

    return this->getObjectAccess()->isSameAs(otherNode->getObjectAccess()) &&
           this->getArguments()->isSameAs(otherNode->getArguments());
}

void ASTObjectAccessInvocationExpressionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _objectAccess->print();
    _arguments->print();
    Logger::log("----------");
}

std::string ASTObjectAccessInvocationExpressionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_objectAccess)
    ->add(_arguments);
    return sourceCodeBuilder.build();
}