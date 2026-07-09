//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_MODULE_LIST_ITEM_NODE_H
#define JETLANG_AST_MODULE_LIST_ITEM_NODE_H

#include <string>
#include <optional>
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-literal-nodes/ast-literal-node.h"
#include "ast-module-list-items/ast-module-list-base-item-node.h"

class ASTModuleListItemNode : public ASTNode {
private:
    std::shared_ptr<ASTModuleListBaseItemNode> _item;
public:
    ASTModuleListItemNode(std::shared_ptr<ASTModuleListBaseItemNode> item);
    std::shared_ptr<ASTModuleListBaseItemNode> getItem();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_LIST_ITEM_NODE_H
