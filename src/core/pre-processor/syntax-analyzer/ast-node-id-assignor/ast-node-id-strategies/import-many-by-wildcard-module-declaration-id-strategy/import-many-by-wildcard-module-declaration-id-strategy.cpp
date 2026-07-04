//
// Created by Johny Georges on 2024-06-05.
//

#include "import-many-by-wildcard-module-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-import-many-by-wildcard-module-declaration-node.h"

void ImportManyByWildcardModuleDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto importManyByWildcardModuleDeclarationNode = std::dynamic_pointer_cast<ASTImportManyByWildcardModuleDeclarationNode>(node);
//    todo: implement once module resolution is implemented
}