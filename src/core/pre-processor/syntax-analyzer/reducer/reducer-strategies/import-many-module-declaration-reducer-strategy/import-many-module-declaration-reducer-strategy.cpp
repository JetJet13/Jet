//
// Created by Johny Georges on 2024-04-15.
//

#include "import-many-module-declaration-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-import-many-module-declaration-node.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-by-wildcard-item-node.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-by-group-item-node.h"
#include "../../../../../ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-wildcard-item-node.h"

ASTNode* ImportManyModuleDeclarationReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 4) {
        throw std::invalid_argument("unable to reduce to import many module declaration since nodes list is not 4");
    }

    if (nodes[1]->is(AST_IMPORT_MODULE_LIST_BY_WILDCARD_ITEM_NODE)) {
        return new ASTImportManyModuleDeclarationNode(
                ((ASTImportModuleListByWildcardItemNode*)nodes[1])->getModuleName(),
                new ASTImportModuleListNode({
                   new ASTImportModuleListItemNode(
                       new ASTImportModuleListWildcardItemNode(
                           ((ASTImportModuleListByWildcardItemNode*)nodes[1])
                           ->getWildcard()
                           ->getLexeme()
                       )
                   )
                }),
                (ASTImportPathNode*)nodes[3]
        );
    }
    return new ASTImportManyModuleDeclarationNode(
            ((ASTImportModuleListByGroupItemNode*)nodes[1])->getModuleName(),
            ((ASTImportModuleListByGroupItemNode*)nodes[1])->getModuleList(),
            (ASTImportPathNode*)nodes[3]
    );
}