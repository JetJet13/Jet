//
// Created by Johny Georges on 2024-06-05.
//

#include "use-many-by-wildcard-module-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-use-many-by-wildcard-module-declaration-node.h"

void UseManyByWildcardModuleDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto useManyByWildcardModuleDeclarationNode = std::dynamic_pointer_cast<ASTUseManyByWildcardModuleDeclarationNode>(node);
//    todo: implement once module resolution is implemented
}