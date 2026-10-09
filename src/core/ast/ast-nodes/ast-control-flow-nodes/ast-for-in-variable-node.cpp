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
// Created by Johny Georges on 2024-03-29.
//

#include "ast-for-in-variable-node.h"
#include "../../../../shared/utils/logger/logger.h"

ASTForInVariableNode::ASTForInVariableNode(std::shared_ptr<ASTIdentifierExpressionNode> variable) {
    _variable = variable;
    _children.push_back(_variable);
    _id = _variable->getId();
}

void ASTForInVariableNode::markAsCaptured() {
    _captureCount++;
}

uint64_t ASTForInVariableNode::getCaptureCount() {
    return _captureCount;
}

bool ASTForInVariableNode::isCaptured() {
    return _captureCount > 0;
}

std::shared_ptr<ASTIdentifierExpressionNode> ASTForInVariableNode::getVariable() {
    return _variable;
}

void ASTForInVariableNode::setTypeSignature(std::shared_ptr<TypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<TypeSignature> ASTForInVariableNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTForInVariableNode::getStartPosition() {
    return _variable->getStartPosition();
}

std::shared_ptr<Position> ASTForInVariableNode::getEndPosition() {
    return _variable->getEndPosition();
}

ASTNodeType ASTForInVariableNode::getNodeType() {
    return AST_FOR_IN_VARIABLE_NODE;
}

std::string ASTForInVariableNode::toString() {
    return "FOR_IN_VARIABLE";
}

bool ASTForInVariableNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTForInVariableNode>(other);
    return this->getVariable()->isSameAs(otherNode->getVariable());
}

void ASTForInVariableNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _variable->print();
    Logger::log("----------");
}

std::string ASTForInVariableNode::toSourceCode() {
    return _variable->toSourceCode();
}