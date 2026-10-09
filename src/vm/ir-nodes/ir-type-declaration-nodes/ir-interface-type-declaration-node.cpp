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
// Created by Johny Georges on 2025-07-04.
//

#include "ir-interface-type-declaration-node.h"

IRInterfaceTypeDeclarationNode::IRInterfaceTypeDeclarationNode(std::shared_ptr<ASTInterfaceTypeDeclarationNode> node, std::shared_ptr<IRStructType> irInterfaceType) {
    _node = node;
    _irInterfaceType = irInterfaceType;
}

std::string IRInterfaceTypeDeclarationNode::getName() {
    return _node->getName()->getId();
}

std::shared_ptr<IRStructType> IRInterfaceTypeDeclarationNode::getIRType() {
    return _irInterfaceType;
}

IRNodeType IRInterfaceTypeDeclarationNode::getNodeType() {
    return IR_INTERFACE_TYPE_DECLARATION_NODE;
}

std::string IRInterfaceTypeDeclarationNode::toString() {
    return "IR_INTERFACE_TYPE_DECLARATION_NODE";
}

void IRInterfaceTypeDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
    _irInterfaceType->print();
}