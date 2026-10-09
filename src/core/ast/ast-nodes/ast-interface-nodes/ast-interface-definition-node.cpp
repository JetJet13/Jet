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

#include "ast-interface-definition-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTInterfaceDefinitionNode::ASTInterfaceDefinitionNode(std::shared_ptr<ASTInterfaceNode> interfaceKeyword, std::shared_ptr<ASTInterfaceNameNode> name) {
    _interfaceKeyword = interfaceKeyword;
    _name = name;
    _children.push_back(_interfaceKeyword);
    _children.push_back(_name);
}


std::shared_ptr<ASTInterfaceNameNode> ASTInterfaceDefinitionNode::getName() {
    return _name;
}

std::shared_ptr<Position> ASTInterfaceDefinitionNode::getStartPosition() {
    return _interfaceKeyword->getStartPosition();
}

std::shared_ptr<Position> ASTInterfaceDefinitionNode::getEndPosition() {
    return _name->getEndPosition();
}

ASTNodeType ASTInterfaceDefinitionNode::getNodeType() {
    return AST_INTERFACE_DEFINITION_NODE;
}

std::string ASTInterfaceDefinitionNode::toString() {
    return "INTERFACE_DEFINITION";
}

bool ASTInterfaceDefinitionNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTInterfaceDefinitionNode>(other);

    return  this->getName()->isSameAs(otherNode->getName());
}

void ASTInterfaceDefinitionNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    Logger::log("----------");
}

std::string ASTInterfaceDefinitionNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_interfaceKeyword);
    sourceCodeBuilder.add(_name);
    return sourceCodeBuilder.build();
}