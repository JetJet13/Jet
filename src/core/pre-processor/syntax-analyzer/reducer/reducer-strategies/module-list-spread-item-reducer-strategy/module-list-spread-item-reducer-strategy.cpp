//
// Created by Johny Georges on 2024-04-13.
//

#include "module-list-spread-item-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-module-nodes/ast-module-list-items/ast-module-list-spread-item-node.h"

std::shared_ptr<ASTNode> ModuleListSpreadItemReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 2) {
        throw std::invalid_argument("unable to reduce to module list spread item since nodes list is not of size 2");
    }

    return std::make_shared<ASTModuleListSpreadItemNode>(
            std::dynamic_pointer_cast<ASTModuleNameNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTModuleSpreadNode>(nodes[0])
    );
}