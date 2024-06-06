//
// Created by Johny Georges on 2024-04-13.
//

#ifndef JETLANG_AST_USE_MANY_MODULE_DECLARATION_NODE_H
#define JETLANG_AST_USE_MANY_MODULE_DECLARATION_NODE_H

#include "../ast-node.h"
#include "../ast-import-nodes/ast-import-module-list-node.h"
#include "../ast-import-nodes/ast-import-path-node.h"
#include "../ast-import-nodes/ast-import-module-name-node.h"
#include "../ast-import-nodes/ast-package-node/ast-use-node.h"
#include "../ast-import-nodes/ast-import-list-items/ast-import-module-list-by-group-item-node.h"
#include "../ast-import-nodes/ast-from-node.h"
#include "ast-declaration-node.h"

class ASTUseManyModuleDeclarationNode : public ASTDeclarationNode {
private:
    ASTUseNode* _useKeyword;
    ASTImportModuleListByGroupItemNode* _importModuleListByGroupItem;
    ASTFromNode* _fromKeyword;
    ASTImportPathNode* _path;
public:
    explicit ASTUseManyModuleDeclarationNode(ASTUseNode* useKeyword, ASTImportModuleListByGroupItemNode* importModuleListByGroupItem, ASTFromNode* fromKeyword, ASTImportPathNode* path);
    ASTImportModuleListByGroupItemNode* getImportModuleListByGroupItem();
    ASTImportModuleNameNode* getModuleName();
    ASTImportModuleListNode* getModuleList();
    ASTImportPathNode* getPath();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_USE_MANY_MODULE_DECLARATION_NODE_H
