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
    ASTUseNode* _useKeyword;
    ASTImportModuleListByWildcardItemNode* _importModuleListByWildcardItemNode;
    ASTFromNode* _fromKeyword;
    ASTImportPathNode* _path;
public:
    ASTUseManyByWildcardModuleDeclarationNode(ASTUseNode* importKeyword, ASTImportModuleListByWildcardItemNode* importModuleListByWildcardItemNode, ASTFromNode* fromKeyword, ASTImportPathNode* path);
    ASTImportModuleListByWildcardItemNode* getImportModuleListByWildcardItemNode();
    ASTImportPathNode* getPath();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_USE_MANY_BY_WILDCARD_MODULE_DECLARATION_NODE_H
