//
// Created by Johny Georges on 2024-10-31.
//

#ifndef JETLANG_FILE_SCOPE_H
#define JETLANG_FILE_SCOPE_H

#include <vector>
#include <optional>
#include "../../../ast/ast-nodes/ast-declaration-nodes/ast-module-declaration-node.h"
#include "../../../ast/ast-nodes/ast-declaration-nodes/ast-import-single-module-declaration-node.h"

class FileScope {
private:
    std::vector<std::shared_ptr<ASTNode>> _scope = std::vector<std::shared_ptr<ASTNode>>();
    std::vector<std::shared_ptr<ASTImportSingleModuleDeclarationNode>> _imports = std::vector<std::shared_ptr<ASTImportSingleModuleDeclarationNode>>();
    std::optional<std::shared_ptr<ASTModuleDeclarationNode>> _module = {};
public:
    FileScope();
    void addToScope(std::shared_ptr<ASTNode> node);
    std::vector<std::shared_ptr<ASTNode>> getScope();
    void setModule(std::shared_ptr<ASTModuleDeclarationNode> node);
    std::optional<std::shared_ptr<ASTModuleDeclarationNode>> getModule();
    void addImport(std::shared_ptr<ASTImportSingleModuleDeclarationNode> node);
    std::vector<std::shared_ptr<ASTImportSingleModuleDeclarationNode>> getImports();
};
#endif //JETLANG_FILE_SCOPE_H
