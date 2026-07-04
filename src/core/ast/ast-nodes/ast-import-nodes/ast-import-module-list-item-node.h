//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_ITEM_NODE_H
#define JETLANG_AST_IMPORT_MODULE_LIST_ITEM_NODE_H

#include <string>
#include <optional>
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-literal-nodes/ast-literal-node.h"
#include "ast-import-list-items/ast-import-module-list-base-item-node.h"

class ASTImportModuleListItemNode : public ASTNode {
private:
    std::shared_ptr<ASTImportModuleListBaseItemNode> _item;
public:
    ASTImportModuleListItemNode(std::shared_ptr<ASTImportModuleListBaseItemNode> item);
    std::shared_ptr<ASTImportModuleListBaseItemNode> getItem();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_ITEM_NODE_H
