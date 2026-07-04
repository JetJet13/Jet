//
// Created by Johny Georges on 2024-04-24.
//

#include "class-property-definition-with-type-reducer-strategy.h"
#include "../../../../../ast/ast-nodes/ast-class-nodes/ast-class-property-definition-with-type-node.h"

std::shared_ptr<ASTNode> ClassPropertyDefinitionWithTypeReducerStrategy::execute(std::vector<std::shared_ptr<ASTNode>> nodes) {
    if (nodes.size() != 3) {
        throw std::invalid_argument("unable to reduce to class property definition with type since nodes list size is not 3");
    }
    return std::make_shared<ASTClassPropertyDefinitionWithTypeNode>(
            std::dynamic_pointer_cast<ASTClassPropertyDefinitionNode>(nodes[0]),
            std::dynamic_pointer_cast<ASTTypeColonNode>(nodes[1]),
            std::dynamic_pointer_cast<ASTTypeNode>(nodes[2])
    );
}