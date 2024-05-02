//
// Created by Johny Georges on 2024-04-13.
//

#ifndef JETLANG_AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE_H
#define JETLANG_AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE_H

#include "../ast-node.h"
#include "../ast-import-nodes/ast-import-module-name-node.h"
#include "../ast-import-nodes/ast-import-path-node.h"
#include "ast-declaration-node.h"

class ASTImportSingleModuleDeclarationNode : public ASTDeclarationNode {
private:
    ASTImportModuleNameNode* _moduleName;
    ASTImportPathNode* _path;
public:
    explicit ASTImportSingleModuleDeclarationNode(ASTImportModuleNameNode* moduleName, ASTImportPathNode* path);
    ASTImportModuleNameNode* getModuleName();
    ASTImportPathNode* getPath();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE_H
