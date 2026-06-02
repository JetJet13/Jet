//
// Created by Johny Georges on 2026-05-30.
//

#include "module-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"

ASTNode* ModuleTypeReducerStrategy::execute(std::vector<ASTNode*> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to module type since nodes list is not of size 2");
    }

    return ASTTypeNodeFactory::createModuleTypeNode(
            new ASTModuleTypeNode(
                (ASTModuleTypeSourceNode*)nodes[0],
                (ASTModuleAccessTypeNode*)nodes[1],
                (ASTModuleTypeTargetNode*)nodes[2]
            )
    );
}