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
    std::shared_ptr<ASTModuleNameNode> _moduleName;
    std::shared_ptr<ASTModuleSpreadNode> _spread;
public:
    explicit ASTModuleListSpreadItemNode(std::shared_ptr<ASTModuleNameNode> moduleName, std::shared_ptr<ASTModuleSpreadNode> spread);
    std::shared_ptr<ASTModuleNameNode> getModuleName();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_LIST_SPREAD_ITEM_NODE_H
