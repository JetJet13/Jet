//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_SPREAD_ITEM_NODE_H
#define JETLANG_AST_IMPORT_MODULE_LIST_SPREAD_ITEM_NODE_H

#include <string>
#include "../../ast-node.h"
#include "ast-import-module-list-base-item-node.h"
#include "../ast-import-module-name-node.h"

class ASTImportModuleListSpreadItemNode : public ASTImportModuleListBaseItemNode {
    ASTImportModuleNameNode* _moduleName;
public:
    explicit ASTImportModuleListSpreadItemNode(ASTImportModuleNameNode* moduleName);
    ASTImportModuleNameNode* getModuleName();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_SPREAD_ITEM_NODE_H
