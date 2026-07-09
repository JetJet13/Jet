//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_NODE_H
#define JETLANG_AST_IMPORT_MODULE_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-import-module-list-item-node.h"
#include "ast-import-module-list-start-node.h"
#include "ast-import-module-list-end-node.h"

class ASTImportModuleListNode : public ASTNode {
private:
    std::shared_ptr<ASTImportModuleListStartNode> _importModuleListStartNode;
    std::shared_ptr<ASTImportModuleListEndNode> _importModuleListEndNode;
    std::vector<std::shared_ptr<ASTImportModuleListItemNode>> _items;
public:
    ASTImportModuleListNode(std::shared_ptr<ASTImportModuleListStartNode> importModuleListStartNode, std::shared_ptr<ASTImportModuleListEndNode> importModuleListEndNode);
    ASTImportModuleListNode(std::shared_ptr<ASTImportModuleListStartNode> importModuleListStartNode, std::vector<std::shared_ptr<ASTImportModuleListItemNode>> items, std::shared_ptr<ASTImportModuleListEndNode> importModuleListEndNode);
    std::vector<std::shared_ptr<ASTImportModuleListItemNode>> getItems();
    unsigned long numItems();
    std::shared_ptr<ASTImportModuleListNode> addItem(std::shared_ptr<ASTImportModuleListItemNode> item);
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_NODE_H
