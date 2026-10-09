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
// Created by Johny Georges on 2024-01-15.
//

#ifndef JETLANG_AST_FILE_NODE_H
#define JETLANG_AST_FILE_NODE_H

#include <filesystem>
#include <vector>
#include "ast-node.h"
#include "ast-block-nodes/ast-block-node.h"
#include "ast-declaration-nodes/ast-import-single-module-declaration-node.h"
#include "ast-declaration-nodes/ast-module-declaration-node.h"

class ASTFileNode : public ASTNode {
private:
    std::filesystem::path _path;
    std::vector<std::shared_ptr<ASTImportSingleModuleDeclarationNode>> _imports;
    std::vector<std::shared_ptr<ASTNode>> _body;
    std::optional<std::shared_ptr<ASTModuleDeclarationNode>> _module = {};
public:
    ASTFileNode(std::vector<std::shared_ptr<ASTNode>> body, std::string path, std::vector<std::shared_ptr<ASTImportSingleModuleDeclarationNode>> imports, std::optional<std::shared_ptr<ASTModuleDeclarationNode>> module = {});
    void append(std::shared_ptr<ASTNode> node);
    std::filesystem::path getPath();
    std::string getPathDirectory();
    void markGlobalVariables();
    void hoistTypes(std::vector<ASTNodeType> astNodeTypes);
    void setupModuleIfNecessary();
    std::optional<std::shared_ptr<ASTModuleDeclarationNode>> getModule();
    std::string getModuleName();
    std::vector<std::shared_ptr<ASTImportSingleModuleDeclarationNode>>* getImports();
    std::vector<std::shared_ptr<ASTNode>>* getBody();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FILE_NODE_H
