//
// Created by Johny Georges on 2024-05-02.
//

#include "import-many-module-declaration-id-strategy.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-import-many-module-declaration-node.h"

void ImportManyModuleDeclarationIdStrategy::assign(std::shared_ptr<ASTNode> node) {
    auto importManyModuleDeclarationNode = std::dynamic_pointer_cast<ASTImportManyModuleDeclarationNode>(node);
//    todo: implement once module resolution is implemented
}