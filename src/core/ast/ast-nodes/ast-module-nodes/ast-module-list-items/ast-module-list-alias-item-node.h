//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_ALIAS_ITEM_NODE_H
#define JETLANG_AST_MODULE_LIST_ALIAS_ITEM_NODE_H

#include <string>
#include "../../ast-node.h"
#include "ast-module-list-base-item-node.h"
#include "../ast-module-name-node.h"
#include "../ast-module-alias-name-node.h"

class ASTImportModuleListAliasItemNode : public ASTModuleListBaseItemNode {
    ASTPackageNameNode* _moduleName;
    ASTPackageAliasNameNode* _aliasModuleName;
public:
    explicit ASTImportModuleListAliasItemNode(ASTPackageNameNode* moduleName, ASTPackageAliasNameNode* aliasModuleName);
    ASTPackageNameNode* getModuleName();
    ASTPackageAliasNameNode* getAliasModuleName();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_ALIAS_ITEM_NODE_H
