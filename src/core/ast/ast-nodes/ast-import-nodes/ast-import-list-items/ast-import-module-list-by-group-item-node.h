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
    std::shared_ptr<ASTImportModuleNameNode> _moduleName;
    std::shared_ptr<ASTModuleAccessNode> _moduleAccessNode;
    std::shared_ptr<ASTImportModuleListNode> _importModuleList;
public:
    explicit ASTImportModuleListByGroupItemNode(std::shared_ptr<ASTImportModuleNameNode> moduleName, std::shared_ptr<ASTModuleAccessNode> moduleAccessNode, std::shared_ptr<ASTImportModuleListNode> importModuleList);
    std::shared_ptr<ASTImportModuleNameNode> getModuleName();
    std::shared_ptr<ASTImportModuleListNode> getModuleList();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_BY_GROUP_ITEM_NODE_H
