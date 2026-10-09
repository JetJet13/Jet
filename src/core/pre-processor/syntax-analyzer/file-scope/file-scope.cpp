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
// Created by Johny Georges on 2024-10-31.
//

#include "file-scope.h"

FileScope::FileScope(std::string filePath) {
    _filePath = std::filesystem::canonical(filePath);
}

std::string FileScope::getFilePath() {
    return _filePath;
}

void FileScope::addToScope(std::shared_ptr<ASTNode> node) {
    _scope.push_back(node);
}

std::vector<std::shared_ptr<ASTNode>> FileScope::getScope() {
    return _scope;
}

void FileScope::setModule(std::shared_ptr<ASTModuleDeclarationNode> node) {
    _module = node;
}

std::optional<std::shared_ptr<ASTModuleDeclarationNode>> FileScope::getModule() {
    return _module;
}

void FileScope::addImport(std::shared_ptr<ASTImportSingleModuleDeclarationNode> node) {
    _imports.push_back(node);
}

std::vector<std::shared_ptr<ASTImportSingleModuleDeclarationNode>> FileScope::getImports() {
    return _imports;
}