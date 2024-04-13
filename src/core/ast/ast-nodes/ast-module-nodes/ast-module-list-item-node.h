//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_ITEM_NODE_H
#define JETLANG_AST_MODULE_LIST_ITEM_NODE_H

#include <string>
#include <optional>
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-literal-nodes/ast-literal-node.h"
#include "ast-module-list-items/ast-module-list-base-item-node.h"

class ASTImportModuleListItemNode : public ASTNode {
private:
    ASTModuleListBaseItemNode* _item;
public:
    ASTImportModuleListItemNode(ASTModuleListBaseItemNode* item);
    ASTModuleListBaseItemNode* getItem();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_ITEM_NODE_H
