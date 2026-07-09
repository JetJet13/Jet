//
// Created by Johny Georges on 2024-04-15.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_NODE_H
#define JETLANG_AST_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_NODE_H

#include <string>
#include "../../ast-node.h"
#include "../../ast-identifier-node.h"
#include "../ast-import-module-name-node.h"
#include "ast-import-module-list-base-item-node.h"
#include "../ast-import-wildcard-node.h"
#include "../../ast-module-nodes/ast-module-access-node.h"


class ASTImportModuleListByWildcardItemNode : public ASTImportModuleListBaseItemNode {
    std::shared_ptr<ASTImportModuleNameNode> _moduleName;
    std::shared_ptr<ASTModuleAccessNode> _moduleAccessNode;
    std::shared_ptr<ASTImportWildcardNode> _wildcard;
public:
    explicit ASTImportModuleListByWildcardItemNode(std::shared_ptr<ASTImportModuleNameNode> moduleName, std::shared_ptr<ASTModuleAccessNode> moduleAccessNode, std::shared_ptr<ASTImportWildcardNode> wildcard);
    std::shared_ptr<ASTImportModuleNameNode> getModuleName();
    std::shared_ptr<ASTImportWildcardNode> getWildcard();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_NODE_H
