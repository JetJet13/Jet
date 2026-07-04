//
// Created by Johny Georges on 2024-06-04.
//

#ifndef JETLANG_AST_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE_H
#define JETLANG_AST_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE_H

#include "../ast-import-nodes/ast-import-list-items/ast-import-module-list-by-wildcard-item-node.h"
#include "ast-declaration-node.h"
#include "../ast-import-nodes/ast-import-path-node.h"
#include "../ast-import-nodes/ast-import-node.h"
#include "../ast-import-nodes/ast-from-node.h"
#include "../ast-import-nodes/ast-package-node/ast-use-node.h"

class ASTUseManyByWildcardModuleDeclarationNode : public ASTDeclarationNode {
private:
    std::shared_ptr<ASTUseNode> _useKeyword;
    std::shared_ptr<ASTImportModuleListByWildcardItemNode> _importModuleListByWildcardItemNode;
    std::shared_ptr<ASTFromNode> _fromKeyword;
    std::shared_ptr<ASTImportPathNode> _path;
public:
    ASTUseManyByWildcardModuleDeclarationNode(std::shared_ptr<ASTUseNode> importKeyword, std::shared_ptr<ASTImportModuleListByWildcardItemNode> importModuleListByWildcardItemNode, std::shared_ptr<ASTFromNode> fromKeyword, std::shared_ptr<ASTImportPathNode> path);
    std::shared_ptr<ASTImportModuleListByWildcardItemNode> getImportModuleListByWildcardItemNode();
    std::shared_ptr<ASTImportPathNode> getPath();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE_H
