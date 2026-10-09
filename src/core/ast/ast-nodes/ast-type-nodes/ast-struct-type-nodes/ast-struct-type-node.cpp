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
// Created by Johny Georges on 2025-06-28.
//

#include "ast-struct-type-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTStructTypeNode::ASTStructTypeNode(std::shared_ptr<ASTStructTypeStartNode> structTypeStartNode, std::shared_ptr<ASTStructTypeEndNode> structTypeEndNode) {
    _structTypeStartNode = structTypeStartNode;
    _structTypeEndNode = structTypeEndNode;
    _commas = std::vector<std::shared_ptr<ASTCommaNode>>();
    _keyValueTypes = std::vector<std::shared_ptr<ASTStructTypeKeyValueNode>>();
}

ASTStructTypeNode::ASTStructTypeNode(std::shared_ptr<ASTStructTypeStartNode> structTypeStartNode, std::vector<std::shared_ptr<ASTStructTypeKeyValueNode>> keyValueTypes, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTStructTypeEndNode> structTypeEndNode) {
    _structTypeStartNode = structTypeStartNode;
    _structTypeEndNode = structTypeEndNode;
    _commas = commas;
    _keyValueTypes = std::vector<std::shared_ptr<ASTStructTypeKeyValueNode>>();
    for (auto keyValueType: keyValueTypes) {
        _keyValueTypes.push_back(keyValueType);
        _children.push_back(keyValueType);
    }
}

std::vector<std::shared_ptr<ASTStructTypeKeyValueNode>> ASTStructTypeNode::getKeyValueTypes() {
    return _keyValueTypes;
}

uint64_t ASTStructTypeNode::numKeyValueTypes() {
    return _keyValueTypes.size();
}

std::shared_ptr<ASTStructTypeNode> ASTStructTypeNode::addKeyValueType(std::shared_ptr<ASTStructTypeKeyValueNode> keyValueType) {
    _keyValueTypes.push_back(keyValueType);
    _children.push_back(keyValueType);
    return std::dynamic_pointer_cast<ASTStructTypeNode>(shared_from_this());
}

std::shared_ptr<ASTStructTypeNode> ASTStructTypeNode::addComma(std::shared_ptr<ASTCommaNode> comma) {
    _commas.push_back(comma);
    return std::dynamic_pointer_cast<ASTStructTypeNode>(shared_from_this());
}

std::shared_ptr<Position> ASTStructTypeNode::getStartPosition() {
    return _structTypeStartNode->getStartPosition();
}

std::shared_ptr<Position> ASTStructTypeNode::getEndPosition() {
    return _structTypeEndNode->getEndPosition();
}

ASTNodeType ASTStructTypeNode::getNodeType() {
    return AST_STRUCT_TYPE_NODE;
}

std::string ASTStructTypeNode::toString() {
    return "STRUCT_TYPE";
}

bool ASTStructTypeNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTStructTypeNode>(other);
    auto otherNodeElements = otherNode->getKeyValueTypes();
    if (this->numKeyValueTypes() != otherNode->numKeyValueTypes()) {
        return false;
    }
    for (uint64_t i = 0; i < this->numKeyValueTypes(); i++) {
        if (!_keyValueTypes[i]->isSameAs(otherNodeElements[i])) {
            return false;
        }
    }

    return true;
}

void ASTStructTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto keyValueType : _keyValueTypes) {
        keyValueType->print();
    }
    Logger::log("----------");
}

std::string ASTStructTypeNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_structTypeStartNode);
    for (uint64_t i = 0; i < _keyValueTypes.size(); ++i) {
        sourceCodeBuilder.add(_keyValueTypes.at(i));
        if (i < _commas.size() ) {
            sourceCodeBuilder.add(_commas.at(i));
        }
    }
    sourceCodeBuilder.add(_structTypeEndNode);
    return sourceCodeBuilder.build();
}