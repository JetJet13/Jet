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
// Created by Johny Georges on 2025-06-25.
//

#include "ast-interface-property-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTInterfacePropertyNode::ASTInterfacePropertyNode(std::shared_ptr<ASTInterfacePropertyNameNode> name, std::shared_ptr<ASTInterfaceColonNode> colon, std::shared_ptr<ASTTypeNode> type) {
    _name = name;
    _colon = colon;
    _type = type;
    _children.push_back(_name);
    _children.push_back(_colon);
    _children.push_back(_type);
}

std::shared_ptr<ASTInterfacePropertyNameNode> ASTInterfacePropertyNode::getName() {
    return _name;
}

std::shared_ptr<ASTTypeNode> ASTInterfacePropertyNode::getType() {
    return _type;
}

void ASTInterfacePropertyNode::setTypeSignature(std::shared_ptr<InterfacePropertyTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<InterfacePropertyTypeSignature> ASTInterfacePropertyNode::getPropertyTypeSignature() {
    return std::dynamic_pointer_cast<InterfacePropertyTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTInterfacePropertyNode::getTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTInterfacePropertyNode::getStartPosition() {
    return _name->getStartPosition();
}

std::shared_ptr<Position> ASTInterfacePropertyNode::getEndPosition() {
    return _type->getEndPosition();
}

ASTNodeType ASTInterfacePropertyNode::getNodeType() {
    return AST_INTERFACE_PROPERTY_NODE;
}

std::string ASTInterfacePropertyNode::toString() {
    return "INTERFACE_PROPERTY";
}

bool ASTInterfacePropertyNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTInterfacePropertyNode>(other);
    return this->getName()->isSameAs(otherNode->getName()) &&
           this->getType()->isSameAs(otherNode->getType());
}

void ASTInterfacePropertyNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _type->print();
    Logger::log("----------");
}

std::string ASTInterfacePropertyNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_name)
    ->add(_colon)
    ->add(_type);
    return sourceCodeBuilder.build();
}