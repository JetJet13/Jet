//
// Created by Johny Georges on 2024-10-31.
//

#include "file-scope.h"

FileScope::FileScope() {}

void FileScope::addToScope(ASTNode* node) {
    _scope.push_back(node);
}

std::vector<ASTNode*> FileScope::getScope() {
    return _scope;
}

void FileScope::setModule(ASTModuleDeclarationNode* node) {
    _module = node;
}

std::optional<ASTModuleDeclarationNode*> FileScope::getModule() {
    return _module;
}

void FileScope::addImport(ASTImportSingleModuleDeclarationNode* node) {
    _imports.push_back(node);
}

std::vector<ASTImportSingleModuleDeclarationNode*> FileScope::getImports() {
    return _imports;
}