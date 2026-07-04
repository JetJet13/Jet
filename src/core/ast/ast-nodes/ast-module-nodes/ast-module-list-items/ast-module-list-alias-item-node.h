//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_MODULE_LIST_ALIAS_ITEM_NODE_H
#define JETLANG_AST_MODULE_LIST_ALIAS_ITEM_NODE_H

#include <string>
#include "../../ast-node.h"
#include "ast-module-list-base-item-node.h"
#include "../ast-module-name-node.h"
#include "../ast-module-alias-name-node.h"
#include "../ast-as-node.h"

class ASTModuleListAliasItemNode : public ASTModuleListBaseItemNode {
    std::shared_ptr<ASTModuleNameNode> _moduleName;
    std::shared_ptr<ASTAsNode> _asNode;
    std::shared_ptr<ASTModuleAliasNameNode> _aliasModuleName;
public:
    explicit ASTModuleListAliasItemNode(std::shared_ptr<ASTModuleNameNode> moduleName, std::shared_ptr<ASTAsNode> asNode, std::shared_ptr<ASTModuleAliasNameNode> aliasModuleName);
    std::shared_ptr<ASTModuleNameNode> getModuleName();
    std::shared_ptr<ASTModuleAliasNameNode> getAliasModuleName();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_LIST_ALIAS_ITEM_NODE_H
