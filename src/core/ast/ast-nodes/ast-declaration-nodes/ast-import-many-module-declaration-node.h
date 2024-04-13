//
// Created by Johny Georges on 2024-04-13.
//

#ifndef JETLANG_AST_IMPORT_MANY_MODULE_DECLARATION_NODE_H
#define JETLANG_AST_IMPORT_MANY_MODULE_DECLARATION_NODE_H

#include "../ast-node.h"
#include "../ast-import-nodes/ast-import-path-node.h"
#include "../ast-import-nodes/ast-import-module-list-node.h"

class ASTImportManyModuleDeclarationNode : public ASTNode {
private:
    ASTImportModuleListNode* _importModuleList;
    ASTImportPathNode* _path;
public:
    explicit ASTImportManyModuleDeclarationNode(ASTImportModuleListNode* importModuleList, ASTImportPathNode* path);
    ASTImportModuleListNode* getModuleList();
    ASTImportPathNode* getPath();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_IMPORT_MANY_MODULE_DECLARATION_NODE_H
