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
// Created by Johny Georges on 2025-07-07.
//

#include "ast-custom-type-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTCustomTypeDeclarationNode::ASTCustomTypeDeclarationNode(std::shared_ptr<ASTTypeKeywordNode> typeKeyword, std::shared_ptr<ASTTypeNameNode> typeName, std::shared_ptr<ASTTypeAssignmentOperatorNode> assignmentOperator, std::shared_ptr<ASTTypeNode> type, std::optional<std::shared_ptr<ASTExportNode>> exportKeyword) {
    _typeKeyword = typeKeyword;
    _typeName = typeName;
    _assignmentOperator = assignmentOperator;
    _type = type;
    _exportKeyword = exportKeyword;
    _children.push_back(_typeKeyword);
    _children.push_back(_typeName);
    _children.push_back(_assignmentOperator);
    _children.push_back(_type);
    if (_exportKeyword) {
        _children.push_back(_exportKeyword.value());
    }
}

std::shared_ptr<ASTTypeNode> ASTCustomTypeDeclarationNode::getType() {
    return _type;
}

std::shared_ptr<ASTTypeNameNode> ASTCustomTypeDeclarationNode::getName() {
    return _typeName;
}

bool ASTCustomTypeDeclarationNode::isExportable() {
    return _exportKeyword.has_value();
}

std::shared_ptr<Position> ASTCustomTypeDeclarationNode::getStartPosition() {
    return _typeKeyword->getStartPosition();
}

std::shared_ptr<Position> ASTCustomTypeDeclarationNode::getEndPosition() {
    return _type->getEndPosition();
}

ASTNodeType ASTCustomTypeDeclarationNode::getNodeType() {
    return AST_CUSTOM_TYPE_DECLARATION_NODE;
}

std::string ASTCustomTypeDeclarationNode::toString() {
    return "CUSTOM_TYPE_DECLARATION";
}

bool ASTCustomTypeDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTCustomTypeDeclarationNode>(other);
    return  this->getName()->isSameAs(otherNode->getName()) &&
            this->getType()->isSameAs(otherNode->getType());
}

void ASTCustomTypeDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    if (_exportKeyword) {
        _exportKeyword.value()->print();
    }
    _typeKeyword->print();
    _typeName->print();
    _assignmentOperator->print();
    _type->print();
    Logger::log("----------");
}

std::string ASTCustomTypeDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    if (_exportKeyword) {
        sourceCodeBuilder.add(_exportKeyword.value())->add(_typeKeyword);
    } else {
        sourceCodeBuilder.add(_typeKeyword);
    }
    sourceCodeBuilder.add(_typeName)
    ->add(_assignmentOperator)
    ->add(_type);
    return sourceCodeBuilder.build();
}