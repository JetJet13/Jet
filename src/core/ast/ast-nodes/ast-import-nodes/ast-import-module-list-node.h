//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_NODE_H
#define JETLANG_AST_IMPORT_MODULE_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-import-module-list-item-node.h"

class ASTImportModuleListNode : public ASTNode {
private:
    std::vector<ASTImportModuleListItemNode*> _items;
public:
    ASTImportModuleListNode();
    ASTImportModuleListNode(std::vector<ASTImportModuleListItemNode*> items);
    std::vector<ASTImportModuleListItemNode*> getItems();
    unsigned long numItems();
    ASTImportModuleListNode* addItem(ASTImportModuleListItemNode* item);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_NODE_H
