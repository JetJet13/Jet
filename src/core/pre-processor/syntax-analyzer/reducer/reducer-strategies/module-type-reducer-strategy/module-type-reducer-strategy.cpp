//
// Created by Johny Georges on 2026-05-30.
//

#include "module-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"

std::shared_ptr<ASTNode> ModuleTypeReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to module type since nodes list is not of size 2");
    }

    return ASTTypeNodeFactory::createModuleTypeNode(
            std::make_shared<ASTModuleTypeNode>(
                std::dynamic_pointer_cast<ASTModuleTypeSourceNode>(nodes[0]),
                std::dynamic_pointer_cast<ASTModuleAccessTypeNode>(nodes[1]),
                std::dynamic_pointer_cast<ASTModuleTypeTargetNode>(nodes[2])
            )
    );
}