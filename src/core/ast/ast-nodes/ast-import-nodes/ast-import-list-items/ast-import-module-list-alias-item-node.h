//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_ALIAS_ITEM_NODE_H
#define JETLANG_AST_IMPORT_MODULE_LIST_ALIAS_ITEM_NODE_H

#include <string>
#include "../../ast-node.h"
#include "ast-import-module-list-base-item-node.h"
#include "../ast-import-module-name-node.h"
#include "../ast-import-module-alias-name-node.h"
#include "../../ast-module-nodes/ast-as-node.h"

class ASTImportModuleListAliasItemNode : public ASTImportModuleListBaseItemNode {
    std::shared_ptr<ASTImportModuleNameNode> _moduleName;
    std::shared_ptr<ASTAsNode> _asKeyword;
    std::shared_ptr<ASTImportModuleAliasNameNode> _aliasModuleName;
public:
    explicit ASTImportModuleListAliasItemNode(std::shared_ptr<ASTImportModuleNameNode> moduleName, std::shared_ptr<ASTAsNode> asKeyword, std::shared_ptr<ASTImportModuleAliasNameNode> aliasModuleName);
    std::shared_ptr<ASTImportModuleNameNode> getModuleName();
    std::shared_ptr<ASTImportModuleAliasNameNode> getAliasModuleName();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_ALIAS_ITEM_NODE_H
