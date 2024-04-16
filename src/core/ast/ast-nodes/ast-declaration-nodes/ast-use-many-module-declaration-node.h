//
// Created by Johny Georges on 2024-04-13.
//

#ifndef JETLANG_AST_USE_MANY_MODULE_DECLARATION_NODE_H
#define JETLANG_AST_USE_MANY_MODULE_DECLARATION_NODE_H

#include "../ast-node.h"
#include "../ast-import-nodes/ast-import-module-list-node.h"
#include "../ast-import-nodes/ast-import-path-node.h"
#include "../ast-import-nodes/ast-import-module-name-node.h"

class ASTUseManyModuleDeclarationNode : public ASTNode {
private:
    ASTImportModuleNameNode* _moduleName;
    ASTImportModuleListNode* _importModuleList;
    ASTImportPathNode* _path;
public:
    explicit ASTUseManyModuleDeclarationNode(ASTImportModuleNameNode* moduleName, ASTImportModuleListNode* importModuleList, ASTImportPathNode* path);
    ASTImportModuleNameNode* getModuleName();
    ASTImportModuleListNode* getModuleList();
    ASTImportPathNode* getPath();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_USE_MANY_MODULE_DECLARATION_NODE_H
