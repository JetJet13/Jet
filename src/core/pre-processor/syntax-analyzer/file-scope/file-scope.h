//
// Created by Johny Georges on 2024-10-31.
//

#ifndef JETLANG_FILE_SCOPE_H
#define JETLANG_FILE_SCOPE_H

#include <vector>
#include <optional>
#include "../../../ast/ast-nodes/ast-declaration-nodes/ast-module-declaration-node.h"

class FileScope {
private:
    std::vector<ASTNode*> _scope = std::vector<ASTNode*>();
    std::optional<ASTModuleDeclarationNode*> _module = {};
public:
    FileScope();
    void addToScope(ASTNode* node);
    std::vector<ASTNode*> getScope();
    void setModule(ASTModuleDeclarationNode* node);
    std::optional<ASTModuleDeclarationNode*> getModule();
};
#endif //JETLANG_FILE_SCOPE_H
