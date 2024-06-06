//
// Created by Johny Georges on 2024-04-16.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_BY_GROUP_ITEM_NODE_H
#define JETLANG_AST_IMPORT_MODULE_LIST_BY_GROUP_ITEM_NODE_H

#include <string>
#include "../../ast-node.h"
#include "../../ast-identifier-node.h"
#include "../ast-import-module-name-node.h"
#include "ast-import-module-list-base-item-node.h"
#include "../ast-import-module-list-node.h"
#include "../../ast-module-nodes/ast-module-access-node.h"


class ASTImportModuleListByGroupItemNode : public ASTImportModuleListBaseItemNode {
    ASTImportModuleNameNode* _moduleName;
    ASTModuleAccessNode* _moduleAccessNode;
    ASTImportModuleListNode* _importModuleList;
public:
    explicit ASTImportModuleListByGroupItemNode(ASTImportModuleNameNode* moduleName, ASTModuleAccessNode* moduleAccessNode, ASTImportModuleListNode* importModuleList);
    ASTImportModuleNameNode* getModuleName();
    ASTImportModuleListNode* getModuleList();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_BY_GROUP_ITEM_NODE_H
