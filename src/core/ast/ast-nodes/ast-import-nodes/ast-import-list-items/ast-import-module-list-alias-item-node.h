//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_ALIAS_ITEM_NODE_H
#define JETLANG_AST_IMPORT_MODULE_LIST_ALIAS_ITEM_NODE_H

#include <string>
#include "../../ast-node.h"
#include "ast-import-module-list-base-item-node.h"
#include "../ast-import-module-name-node.h"
#include "../ast-import-module-alias-name-node.h"
#include "../../ast-module-nodes/ast-as-node.h"

class ASTImportModuleListAliasItemNode : public ASTImportModuleListBaseItemNode {
    ASTImportModuleNameNode* _moduleName;
    ASTAsNode* _asKeyword;
    ASTImportModuleAliasNameNode* _aliasModuleName;
public:
    explicit ASTImportModuleListAliasItemNode(ASTImportModuleNameNode* moduleName, ASTAsNode* asKeyword, ASTImportModuleAliasNameNode* aliasModuleName);
    ASTImportModuleNameNode* getModuleName();
    ASTImportModuleAliasNameNode* getAliasModuleName();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_ALIAS_ITEM_NODE_H
