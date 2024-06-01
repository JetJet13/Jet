//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_MODULE_LIST_SPREAD_ITEM_NODE_H
#define JETLANG_AST_MODULE_LIST_SPREAD_ITEM_NODE_H

#include <string>
#include "../../ast-node.h"
#include "ast-module-list-base-item-node.h"
#include "../ast-module-name-node.h"
#include "../ast-module-spread-node.h"

class ASTModuleListSpreadItemNode : public ASTModuleListBaseItemNode {
private:
    ASTModuleNameNode* _moduleName;
    ASTModuleSpreadNode* _spread;
public:
    explicit ASTModuleListSpreadItemNode(ASTModuleNameNode* moduleName, ASTModuleSpreadNode* spread);
    ASTModuleNameNode* getModuleName();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_LIST_SPREAD_ITEM_NODE_H
