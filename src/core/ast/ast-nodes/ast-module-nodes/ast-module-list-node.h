//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_MODULE_LIST_NODE_H
#define JETLANG_AST_MODULE_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-module-list-item-node.h"
#include "ast-module-list-start-node.h"
#include "ast-module-list-end-node.h"

class ASTModuleListNode : public ASTNode {
private:
    ASTModuleListStartNode* _moduleListStartNode;
    ASTModuleListEndNode* _moduleListEndNode;
    std::vector<ASTModuleListItemNode*> _items;
public:
    ASTModuleListNode(ASTModuleListStartNode* moduleListStartNode, ASTModuleListEndNode* moduleListEndNode);
    ASTModuleListNode(ASTModuleListStartNode* moduleListStartNode, std::vector<ASTModuleListItemNode*> items, ASTModuleListEndNode* moduleListEndNode);
    std::vector<ASTModuleListItemNode*> getItems();
    unsigned long numItems();
    ASTModuleListNode* addItem(ASTModuleListItemNode* item);
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_LIST_NODE_H
