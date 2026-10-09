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
// Created by Johny Georges on 2024-02-08.
//

#include "ast-variable-init-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTVariableInitNode::ASTVariableInitNode(std::shared_ptr<ASTVariableTypeNode> assignmentTypeQualifier, std::shared_ptr<ASTIdentifierNode> astIdentifierNode, std::shared_ptr<ASTAssignmentOperatorNode> assignmentOperator, std::optional<std::shared_ptr<ASTTypeColonNode>> colon, std::optional<std::shared_ptr<ASTTypeNode>> type) {
    _assignmentTypeQualifier = assignmentTypeQualifier;
    _identifier = astIdentifierNode;
    _colon = colon;
    _type = type;
    _assignmentOperator = assignmentOperator;
    _children.push_back(_assignmentTypeQualifier);
    _children.push_back(_identifier);
    if (_type) {
        _children.push_back(_type.value());
    }
}

std::shared_ptr<ASTVariableTypeNode> ASTVariableInitNode::getVarTypeNode() {
    return _assignmentTypeQualifier;
}

std::shared_ptr<ASTIdentifierNode> ASTVariableInitNode::getIdentifierNode() {
    return _identifier;
}

std::optional<std::shared_ptr<ASTTypeNode>> ASTVariableInitNode::getTypeNode() {
    return _type;
}

bool ASTVariableInitNode::isConst() {
    return _assignmentTypeQualifier->isConst();
}

std::shared_ptr<Position> ASTVariableInitNode::getStartPosition() {
    return _assignmentTypeQualifier->getStartPosition();
}

std::shared_ptr<Position> ASTVariableInitNode::getEndPosition() {
    return _assignmentOperator->getEndPosition();
}

ASTNodeType ASTVariableInitNode::getNodeType() {
    return AST_VARIABLE_INIT_NODE;
}

std::string ASTVariableInitNode::toString() {
    return "VARIABLE_INIT";
}

bool ASTVariableInitNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTVariableInitNode>(other);

    if (!_type.has_value() && otherNode->getTypeNode().has_value() ||
            _type.has_value() && !otherNode->getTypeNode().has_value()) {
        return false;
    }

    if (_type.has_value() && otherNode->getTypeNode().has_value() &&
        !_type.value()->isSameAs(otherNode->getTypeNode().value())) {
        return false;
    }

    return this->getVarTypeNode()->isSameAs(otherNode->getVarTypeNode()) &&
           this->getIdentifierNode()->isSameAs(otherNode->getIdentifierNode());
}

void ASTVariableInitNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _assignmentTypeQualifier->print();
    _identifier->print();
    if (_type) {
        _type.value()->print();
    }
    _assignmentOperator->print();
    Logger::log("----------");
}

std::string ASTVariableInitNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_assignmentTypeQualifier)->add(_identifier);

    if (_colon && _type) {
        sourceCodeBuilder.add(_colon.value())->add(_type.value());
    }
    sourceCodeBuilder.add(_assignmentOperator);
    return sourceCodeBuilder.build();
}