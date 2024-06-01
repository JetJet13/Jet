//
// Created by Johny Georges on 2024-04-13.
//

#ifndef JETLANG_AST_IMPORT_MANY_MODULE_DECLARATION_NODE_H
#define JETLANG_AST_IMPORT_MANY_MODULE_DECLARATION_NODE_H

#include "../ast-node.h"
#include "../ast-import-nodes/ast-import-path-node.h"
#include "ast-declaration-node.h"
#include "../ast-import-nodes/ast-import-node.h"
#include "../ast-import-nodes/ast-from-node.h"
#include "../ast-import-nodes/ast-import-list-items/ast-import-module-list-by-group-item-node.h"

class ASTImportManyModuleDeclarationNode : public ASTDeclarationNode {
protected:
    ASTImportNode* _importKeyword;
    ASTImportModuleListByGroupItemNode* _importModuleListByGroupItem;
    ASTFromNode* _fromKeyword;
    ASTImportPathNode* _path;
public:
    explicit ASTImportManyModuleDeclarationNode(ASTImportNode* importKeyword, ASTImportModuleListByGroupItemNode* importModuleListByGroupItem, ASTFromNode* fromKeyword, ASTImportPathNode* path);
    ASTImportModuleNameNode* getModuleName();
    ASTImportModuleListNode* getModuleList();
    ASTImportPathNode* getPath();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPORT_MANY_MODULE_DECLARATION_NODE_H
