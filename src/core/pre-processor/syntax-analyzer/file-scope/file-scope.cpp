//
// Created by Johny Georges on 2024-10-31.
//

#include "file-scope.h"

FileScope::FileScope() {}

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