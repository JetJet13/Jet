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
// Created by Johny Georges on 2024-03-22.
//

#include "ast-enum-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTEnumDeclarationNode::ASTEnumDeclarationNode(std::shared_ptr<ASTEnumNode> enumKeyword, std::shared_ptr<ASTEnumNameNode> name, std::shared_ptr<ASTEnumKeyValueListNode> values, std::optional<std::shared_ptr<ASTExportNode>> exportKeyword) {
    _enumKeyword = enumKeyword;
    _name = name;
    _values = values;
    _exportKeyword = exportKeyword;
    _children.push_back(_enumKeyword);
    _children.push_back(_name);
    _children.push_back(_values);
    if (_exportKeyword) {
        _children.push_back(_exportKeyword.value());
    }
}

std::shared_ptr<ASTEnumKeyValueListNode> ASTEnumDeclarationNode::getValues() {
    return _values;
}

std::shared_ptr<ASTEnumNameNode> ASTEnumDeclarationNode::getName() {
    return _name;
}

void ASTEnumDeclarationNode::setTypeSignature(std::shared_ptr<EnumTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<EnumTypeSignature> ASTEnumDeclarationNode::getEnumTypeSignature() {
    return std::dynamic_pointer_cast<EnumTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTEnumDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

bool ASTEnumDeclarationNode::isExportable() {
    return _exportKeyword.has_value();
}

std::shared_ptr<Position> ASTEnumDeclarationNode::getStartPosition() {
    return _enumKeyword->getStartPosition();
}

std::shared_ptr<Position> ASTEnumDeclarationNode::getEndPosition() {
    return _values->getEndPosition();
}

ASTNodeType ASTEnumDeclarationNode::getNodeType() {
    return AST_ENUM_DECLARATION_NODE;
}

std::string ASTEnumDeclarationNode::toString() {
    return "ENUM_DECLARATION";
}

bool ASTEnumDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTEnumDeclarationNode>(other);

    return  this->getName()->isSameAs(otherNode->getName()) &&
            this->getValues()->isSameAs(otherNode->getValues());
}

void ASTEnumDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _values->print();
    Logger::log("----------");
}

std::string ASTEnumDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_enumKeyword)
    ->add(_name)
    ->add(_values);
    return sourceCodeBuilder.build();
}