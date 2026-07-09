//
// Created by Johny Georges on 2024-06-01.
//

#ifndef JETLANG_AST_IMPORT_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE_H
#define JETLANG_AST_IMPORT_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE_H

#include "../ast-import-nodes/ast-import-list-items/ast-import-module-list-by-wildcard-item-node.h"
#include "ast-declaration-node.h"
#include "../ast-import-nodes/ast-import-path-node.h"
#include "../ast-import-nodes/ast-import-node.h"
#include "../ast-import-nodes/ast-from-node.h"

class ASTImportManyByWildcardModuleDeclarationNode : public ASTDeclarationNode {
private:
    std::shared_ptr<ASTImportNode> _importKeyword;
    std::shared_ptr<ASTImportModuleListByWildcardItemNode> _importModuleListByWildcardItemNode;
    std::shared_ptr<ASTFromNode> _fromKeyword;
    std::shared_ptr<ASTImportPathNode> _path;
public:
    ASTImportManyByWildcardModuleDeclarationNode(std::shared_ptr<ASTImportNode> importKeyword, std::shared_ptr<ASTImportModuleListByWildcardItemNode> importModuleListByWildcardItemNode, std::shared_ptr<ASTFromNode> fromKeyword, std::shared_ptr<ASTImportPathNode> path);
    std::shared_ptr<ASTImportModuleListByWildcardItemNode> getImportModuleListByWildcardItemNode();
    std::shared_ptr<ASTImportPathNode> getPath();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPORT_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE_H
