//
// Created by Johny Georges on 2024-05-03.
//

#include "use-many-module-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-use-many-module-declaration-node.h"

void UseManyModuleDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto useManyModuleDeclarationNode = std::dynamic_pointer_cast<ASTUseManyModuleDeclarationNode>(node);
//    todo: implement once module resolution is implemented
}