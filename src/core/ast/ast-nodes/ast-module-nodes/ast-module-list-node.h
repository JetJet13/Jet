//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_MODULE_LIST_NODE_H
#define JETLANG_AST_MODULE_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-module-list-item-node.h"

class ASTModuleListNode : public ASTNode {
private:
    std::vector<ASTModuleListItemNode*> _items;
public:
    ASTModuleListNode();
    ASTModuleListNode(std::vector<ASTModuleListItemNode*> items);
    std::vector<ASTModuleListItemNode*> getItems();
    unsigned long numItems();
    ASTModuleListNode* addItem(ASTModuleListItemNode* item);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_MODULE_LIST_NODE_H
