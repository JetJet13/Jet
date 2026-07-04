//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_NORMAL_ITEM_NODE_H
#define JETLANG_AST_IMPORT_MODULE_LIST_NORMAL_ITEM_NODE_H

#include <string>
#include "../../ast-node.h"
#include "../../ast-identifier-node.h"
#include "../ast-import-module-name-node.h"
#include "ast-import-module-list-base-item-node.h"


class ASTImportModuleListNormalItemNode : public ASTImportModuleListBaseItemNode {
    std::shared_ptr<ASTImportModuleNameNode> _moduleName;
public:
    explicit ASTImportModuleListNormalItemNode(std::shared_ptr<ASTImportModuleNameNode> moduleName);
    std::shared_ptr<ASTImportModuleNameNode> getModuleName();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_NORMAL_ITEM_NODE_H
