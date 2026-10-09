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

#include "ast-node.h"

#include "../../../shared/utils/logger/logger.h"
#include "../../../shared/utils/to-string/to-string.h"

std::string ASTNode::getId() {
    return _id;
}

std::string ASTNode::getFilePath() {
    return _filePath;
}

std::shared_ptr<ASTNode> ASTNode::setId(std::string id) {
    _id = id;
    return shared_from_this();
}

std::shared_ptr<ASTNode> ASTNode::setFilePath(std::string filePath) {
    _filePath = filePath;
    return shared_from_this();
}

std::optional<std::shared_ptr<ASTNode>> ASTNode::getParentNode() {
    return _parentNode;
}

void ASTNode::setParentNode(std::shared_ptr<ASTNode> parentNode) {
    _parentNode = parentNode;
}

void ASTNode::markAsGlobal() {
    _isGlobal = true;
}

void ASTNode::markAsGrouped() {
    _isGrouped = true;
}

bool ASTNode::isGrouped() {
    return _isGrouped;
}

bool ASTNode::is(ASTNodeType astNodeType) {
    return this->getNodeType() == astNodeType;
}

bool ASTNode::isOneOf(std::vector<ASTNodeType> astNodeTypes) {
    return std::find(
            astNodeTypes.begin(),
            astNodeTypes.end(),
            this->getNodeType()) != astNodeTypes.end();
}

bool ASTNode::isSameNodeTypeAs(std::shared_ptr<ASTNode> other) {
    return this->getNodeType() == other->getNodeType();
}

void ASTNode::print() {
    Logger::log(this->toString());
}

std::string ASTNode::toSourceCode() {
    throw std::logic_error("toSourceCode not implemented: " + this->toString());
}

std::shared_ptr<TypeSignature> ASTNode::getTypeSignature() {
    throw std::logic_error("get type-signature not implemented: " + this->toString());
}

std::vector<std::shared_ptr<ASTNode>> ASTNode::getChildren() {
    return _children;
}

bool ASTNode::isExportable() {
    return false;
}

bool ASTNode::isGlobal() {
    return _isGlobal;
}

unsigned int ASTNode::getPriority() {
    return _priority;
}

bool ASTNode::isHigherPriorityThan(std::shared_ptr<ASTNode> other) {
    return this->getPriority() < other->getPriority();
}

bool ASTNode::isLowerPriorityThan(std::shared_ptr<ASTNode> other) {
    return this->getPriority() > other->getPriority();
}

std::shared_ptr<Position> ASTNode::getStartPosition() {
    throw std::logic_error("get start-position not implemented: " + this->toString());
}

std::shared_ptr<Position> ASTNode::getEndPosition() {
    throw std::logic_error("get end-position not implemented: " + this->toString());
}

std::string ASTNode::getLineColumn() {
    return ToStringUtil::toString(this->getStartPosition()->getLine())
    + ":"
    + ToStringUtil::toString(this->getStartPosition()->getColumn());
}

bool ASTNode::isSameAs(std::shared_ptr<ASTNode> other) {
    return this->getNodeType() == other->getNodeType();
}

bool ASTNode::isExpression() {
    return false;
}

bool ASTNode::isScopedBlockNode() {
    return false;
}

std::shared_ptr<ASTNode> ASTNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) {
    return shared_from_this();
}