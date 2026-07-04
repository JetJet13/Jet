//
// Created by Johny Georges on 2024-04-13.
//

#ifndef JETLANG_AST_USE_MANY_MODULE_DECLARATION_NODE_H
#define JETLANG_AST_USE_MANY_MODULE_DECLARATION_NODE_H

#include "../ast-node.h"
#include "../ast-import-nodes/ast-import-module-list-node.h"
#include "../ast-import-nodes/ast-import-path-node.h"
#include "../ast-import-nodes/ast-import-module-name-node.h"
#include "../ast-import-nodes/ast-package-node/ast-use-node.h"
#include "../ast-import-nodes/ast-import-list-items/ast-import-module-list-by-group-item-node.h"
#include "../ast-import-nodes/ast-from-node.h"
#include "ast-declaration-node.h"

class ASTUseManyModuleDeclarationNode : public ASTDeclarationNode {
private:
    std::shared_ptr<ASTUseNode> _useKeyword;
    std::shared_ptr<ASTImportModuleListByGroupItemNode> _importModuleListByGroupItem;
    std::shared_ptr<ASTFromNode> _fromKeyword;
    std::shared_ptr<ASTImportPathNode> _path;
public:
    explicit ASTUseManyModuleDeclarationNode(std::shared_ptr<ASTUseNode> useKeyword, std::shared_ptr<ASTImportModuleListByGroupItemNode> importModuleListByGroupItem, std::shared_ptr<ASTFromNode> fromKeyword, std::shared_ptr<ASTImportPathNode> path);
    std::shared_ptr<ASTImportModuleListByGroupItemNode> getImportModuleListByGroupItem();
    std::shared_ptr<ASTImportModuleNameNode> getModuleName();
    std::shared_ptr<ASTImportModuleListNode> getModuleList();
    std::shared_ptr<ASTImportPathNode> getPath();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_USE_MANY_MODULE_DECLARATION_NODE_H
