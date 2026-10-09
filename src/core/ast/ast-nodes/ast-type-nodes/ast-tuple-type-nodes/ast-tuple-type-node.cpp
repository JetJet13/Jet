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
// Created by Johny Georges on 2026-03-14.
//

#include "ast-tuple-type-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTTupleTypeNode::ASTTupleTypeNode(std::shared_ptr<ASTTupleTypeStartNode> tupleTypeStartNode, std::shared_ptr<ASTTupleTypeEndNode> tupleTypeEndNode) {
    _tupleTypeStartNode = tupleTypeStartNode;
    _tupleTypeEndNode = tupleTypeEndNode;
    _commas = std::vector<std::shared_ptr<ASTCommaNode>>();
    _types = std::vector<std::shared_ptr<ASTTypeNode>>();
}

ASTTupleTypeNode::ASTTupleTypeNode(std::shared_ptr<ASTTupleTypeStartNode> tupleTypeStartNode, std::vector<std::shared_ptr<ASTTypeNode>> valueTypes, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTTupleTypeEndNode> tupleTypeEndNode) {
    _tupleTypeStartNode = tupleTypeStartNode;
    _tupleTypeEndNode = tupleTypeEndNode;
    _commas = commas;
    _types = std::vector<std::shared_ptr<ASTTypeNode>>();
    for (auto keyValueType: valueTypes) {
        _types.push_back(keyValueType);
        _children.push_back(keyValueType);
    }
}

std::vector<std::shared_ptr<ASTTypeNode>> ASTTupleTypeNode::getValueTypes() {
    return _types;
}

uint64_t ASTTupleTypeNode::numValueTypes() {
    return _types.size();
}

std::shared_ptr<ASTTupleTypeNode> ASTTupleTypeNode::addValueType(std::shared_ptr<ASTTypeNode> type) {
    _types.push_back(type);
    _children.push_back(type);
    return std::dynamic_pointer_cast<ASTTupleTypeNode>(shared_from_this());
}

std::shared_ptr<ASTTupleTypeNode> ASTTupleTypeNode::addComma(std::shared_ptr<ASTCommaNode> comma) {
    _commas.push_back(comma);
    return std::dynamic_pointer_cast<ASTTupleTypeNode>(shared_from_this());
}

std::shared_ptr<Position> ASTTupleTypeNode::getStartPosition() {
    return _tupleTypeStartNode->getStartPosition();
}

std::shared_ptr<Position> ASTTupleTypeNode::getEndPosition() {
    return _tupleTypeEndNode->getEndPosition();
}

ASTNodeType ASTTupleTypeNode::getNodeType() {
    return AST_TUPLE_TYPE_NODE;
}

std::string ASTTupleTypeNode::toString() {
    return "TUPLE_TYPE";
}

bool ASTTupleTypeNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTTupleTypeNode>(other);
    auto otherNodeElements = otherNode->getValueTypes();
    if (this->numValueTypes() != otherNode->numValueTypes()) {
        return false;
    }
    for (uint64_t i = 0; i < this->numValueTypes(); i++) {
        if (!_types[i]->isSameAs(otherNodeElements[i])) {
            return false;
        }
    }

    return true;
}

void ASTTupleTypeNode::print() {
    Logger::log("----------", this->toString(), "----------");
    for (auto valueType : _types) {
        valueType->print();
    }
    Logger::log("----------");
}

std::string ASTTupleTypeNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_tupleTypeStartNode);
    for (uint64_t i = 0; i < _types.size(); ++i) {
        sourceCodeBuilder.add(_types.at(i));
        if (i < _commas.size() ) {
            sourceCodeBuilder.add(_commas.at(i));
        }
    }
    sourceCodeBuilder.add(_tupleTypeEndNode);
    return sourceCodeBuilder.build();
}