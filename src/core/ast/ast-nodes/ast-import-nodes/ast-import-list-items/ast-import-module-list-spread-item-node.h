//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_SPREAD_ITEM_NODE_H
#define JETLANG_AST_IMPORT_MODULE_LIST_SPREAD_ITEM_NODE_H

#include <string>
#include "../../ast-node.h"
#include "ast-import-module-list-base-item-node.h"
#include "../ast-import-module-name-node.h"
#include "../ast-import-spread-node.h"

class ASTImportModuleListSpreadItemNode : public ASTImportModuleListBaseItemNode {
    std::shared_ptr<ASTImportSpreadNode> _spread;
    std::shared_ptr<ASTImportModuleNameNode> _moduleName;
public:
    explicit ASTImportModuleListSpreadItemNode(std::shared_ptr<ASTImportSpreadNode> spread, std::shared_ptr<ASTImportModuleNameNode> moduleName);
    std::shared_ptr<ASTImportModuleNameNode> getModuleName();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_SPREAD_ITEM_NODE_H
