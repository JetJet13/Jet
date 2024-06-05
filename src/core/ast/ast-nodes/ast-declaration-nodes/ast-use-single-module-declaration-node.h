//
// Created by Johny Georges on 2024-04-13.
//

#ifndef JETLANG_AST_USE_SINGLE_MODULE_DECLARATION_NODE_H
#define JETLANG_AST_USE_SINGLE_MODULE_DECLARATION_NODE_H

#include "../ast-node.h"
#include "../ast-import-nodes/ast-import-module-name-node.h"
#include "../ast-import-nodes/ast-import-path-node.h"
#include "ast-declaration-node.h"
#include "../ast-import-nodes/ast-from-node.h"
#include "../ast-import-nodes/ast-package-node/ast-use-node.h"

class ASTUseSingleModuleDeclarationNode : public ASTDeclarationNode {
private:
    ASTUseNode* _useKeyword;
    ASTImportModuleNameNode* _moduleName;
    ASTFromNode* _fromKeyword;
    ASTImportPathNode* _path;
public:
    explicit ASTUseSingleModuleDeclarationNode(ASTUseNode* useKeyword, ASTImportModuleNameNode* moduleName, ASTFromNode* fromKeyword, ASTImportPathNode* path);
    ASTImportModuleNameNode* getModuleName();
    ASTImportPathNode* getPath();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_USE_SINGLE_MODULE_DECLARATION_NODE_H
