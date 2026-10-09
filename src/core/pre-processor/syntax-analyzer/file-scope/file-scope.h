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

#ifndef JETLANG_FILE_SCOPE_H
#define JETLANG_FILE_SCOPE_H

#include <vector>
#include <optional>
#include <filesystem>
#include "../../../ast/ast-nodes/ast-declaration-nodes/ast-module-declaration-node.h"
#include "../../../ast/ast-nodes/ast-declaration-nodes/ast-import-single-module-declaration-node.h"

class FileScope {
private:
    std::string _filePath;
    std::vector<std::shared_ptr<ASTNode>> _scope = std::vector<std::shared_ptr<ASTNode>>();
    std::vector<std::shared_ptr<ASTImportSingleModuleDeclarationNode>> _imports = std::vector<std::shared_ptr<ASTImportSingleModuleDeclarationNode>>();
    std::optional<std::shared_ptr<ASTModuleDeclarationNode>> _module = {};
public:
    FileScope(std::string filePath);
    std::string getFilePath();
    void addToScope(std::shared_ptr<ASTNode> node);
    std::vector<std::shared_ptr<ASTNode>> getScope();
    void setModule(std::shared_ptr<ASTModuleDeclarationNode> node);
    std::optional<std::shared_ptr<ASTModuleDeclarationNode>> getModule();
    void addImport(std::shared_ptr<ASTImportSingleModuleDeclarationNode> node);
    std::vector<std::shared_ptr<ASTImportSingleModuleDeclarationNode>> getImports();
};
#endif //JETLANG_FILE_SCOPE_H
