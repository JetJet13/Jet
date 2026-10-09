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
// Created by Johny Georges on 2024-11-04.
//

#include "jet-file.h"

#include <utility>
#include "jet-file-id-generator/jet-file-id-generator.h"
#include "../../shared/utils/logger/logger.h"

JetFile::JetFile(std::shared_ptr<ASTFileNode> astFileNode, std::shared_ptr<TypeSignatureLookupTable> fileScope, TypeCheckerResult typeCheckerResult, std::set<std::shared_ptr<JetFile>> importedJetFiles) {
    _astFileNode = astFileNode;
    _fileScope = fileScope;
    _typeCheckerResult = std::move(typeCheckerResult);
    _importedJetFiles = std::move(importedJetFiles);
    _id = JetFileIdGenerator::generate(astFileNode->getPath());
}

JetFile::JetFile(std::shared_ptr<ASTFileNode> astFileNode, std::shared_ptr<TypeSignatureLookupTable> fileScope, TypeCheckerResult typeCheckerResult) {
    _astFileNode = astFileNode;
    _fileScope = fileScope;
    _typeCheckerResult = std::move(typeCheckerResult);
    _importedJetFiles = std::set<std::shared_ptr<JetFile>>();
    _id = JetFileIdGenerator::generate(astFileNode->getPath());
}

std::string JetFile::getId() {
    return _id;
}

std::shared_ptr<ASTFileNode> JetFile::getFile() {
    return _astFileNode;
}

std::shared_ptr<TypeSignatureLookupTable> JetFile::getScope() {
    return _fileScope;
}

TypeCheckerResult* JetFile::getTypeCheckerResult() {
    return &_typeCheckerResult;
}

void JetFile::addImportedFile(std::shared_ptr<JetFile> jetFile) {
    _importedJetFiles.insert(jetFile);
}

std::set<std::shared_ptr<JetFile>>* JetFile::getImportedFiles() {
    return &_importedJetFiles;
}

bool JetFile::isModule() {
    return _astFileNode->getModule().has_value();
}

bool JetFile::hasImports() {
    return !_importedJetFiles.empty();
}

void JetFile::print() {
    Logger::log("--- JET FILE ---");
    Logger::log("id:", this->getId());
    this->_astFileNode->print();
}