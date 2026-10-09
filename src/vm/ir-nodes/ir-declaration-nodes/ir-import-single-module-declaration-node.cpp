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
// Created by Johny Georges on 2024-10-30.
//

#include "ir-import-single-module-declaration-node.h"

IRImportSingleModuleDeclarationNode::IRImportSingleModuleDeclarationNode(std::shared_ptr<ASTImportSingleModuleDeclarationNode> node) {
    _node = node;
}

llvm::Value* IRImportSingleModuleDeclarationNode::getValue() {
    // todo - fix;
    return nullptr;
}

IRNodeType IRImportSingleModuleDeclarationNode::getNodeType() {
    return IR_IMPORT_SINGLE_MODULE_DECLARATION_NODE;
}

std::string IRImportSingleModuleDeclarationNode::toString() {
    return "IR_IMPORT_SINGLE_MODULE_DECLARATION_NODE";
}

void IRImportSingleModuleDeclarationNode::print(std::unique_ptr<llvm::raw_fd_ostream> *stream) {
}