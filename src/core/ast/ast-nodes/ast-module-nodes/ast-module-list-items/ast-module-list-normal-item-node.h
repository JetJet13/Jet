//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_NORMAL_ITEM_NODE_H
#define JETLANG_AST_MODULE_LIST_NORMAL_ITEM_NODE_H

#include <string>
#include "../../ast-node.h"
#include "ast-module-list-base-item-node.h"
#include "../../ast-identifier-node.h"
#include "../ast-module-name-node.h"

class ASTModuleListNormalItemNode : public ASTModuleListBaseItemNode {
    ASTModuleNameNode* _moduleName;
public:
    explicit ASTModuleListNormalItemNode(ASTModuleNameNode* moduleName);
    ASTModuleNameNode* getModuleName();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_NORMAL_ITEM_NODE_H
