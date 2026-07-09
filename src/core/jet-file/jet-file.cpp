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